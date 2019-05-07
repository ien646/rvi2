#include <rvi/client_instance.hpp>

#include <map>
#include <optional>
#include <functional>

#include <rvi/runtime.hpp>

using std::vector;
using std::string;
using std::unordered_map;

namespace rvi
{
    client_instance::client_instance(runtime* rptr, rvi_cid_t cid)
        : _ctx(std::make_unique<client_context>())
        , _lua_ctx(std::make_unique<lua_context>(this))
        , _runtime_ptr(rptr)
        , _cid(cid)
    { }

    void client_instance::reload()
    {
        this->_clickable_frames.clear();
        this->_ctx = std::make_unique<client_context>();
        this->_lua_ctx = std::make_unique<lua_context>(this);
        this->_macros.clear();
        _runtime_ptr->start_client(_cid);
    }

    client_context* client_instance::get_context()
    {
        return _ctx.get();
    }

    runtime* client_instance::get_runtime()
    {
        return _runtime_ptr;
    }

    rvi_cid_t client_instance::client_id()
    {
        return _cid;
    }

    void client_instance::define_macro(const string& name, const vector<string>& funs)
    {
        if(_macros.count(name) > 0)
        {
            _macros.erase(name);
        }
        _macros.emplace(name, funs);
    }

    void client_instance::undefine_macro(const std::string& name)
    {
        _macros.erase(name);
    }

    void client_instance::exec_macro(const std::string& mname)
    {
        if(_macros.count(mname) > 0)
        {
            auto& macro = _macros.at(mname);
            for(auto& entry : macro)
            {
                _lua_ctx->exec_script(entry);
            }
        }
    }
    
    std::optional<std::reference_wrapper<std::vector<std::string>>>
    client_instance::get_macro(const string& name)
    {
        if(_macros.count(name) > 0)
        {
            return _macros.at(name);
        }
        return std::optional<std::reference_wrapper<std::vector<std::string>>>();
    }

    void client_instance::run_script_file(const std::string& filepath)
    {
        _lua_ctx->exec_script_file(filepath);
    }

    void client_instance::set_current_frame_clickable(const std::string& call)
    {
        frame* fptr = _ctx->selected_frame();
        clickable_frame_data fdata(fptr, call);
        _clickable_frames.emplace(fptr, fdata);
    }

    void client_instance::unset_current_frame_clickable()
    {
        _clickable_frames.erase(_ctx->selected_frame());
    }

    void client_instance::user_click(vector2 pos)
    {
        auto& ctx_frames = _ctx->frames();
        std::map<uint64_t, frame*> hits;
        vector<frame*> pending_delete;

        // Get hits
        for(auto& entry : _clickable_frames)
        {
            clickable_frame_data& fdata = entry.second;
            if(fdata.rect.contains(pos))
            {
                frame* fptr = fdata.fptr;
                if(ctx_frames.count(fptr) == 0)
                {
                    pending_delete.push_back(fptr);
                }
                else
                {
                    hits.emplace(fdata.uid, fptr);
                }
            }
        }

        // Remove deleted hit frames
        for(frame* fptr : pending_delete)
        {
            _clickable_frames.erase(fptr);
        }

        if(hits.empty()) { return; }

        // Hit frame with the latest uid (added last)
        auto pair = *(hits.rbegin()); // std::map keys are ordered
        auto& binding_name = _clickable_frames.at(pair.second).binding_name;
        _runtime_ptr->exec_binding(*this, binding_name, pair.second);
    }

    const std::unordered_map<std::string, std::vector<std::string>>& client_instance::macros()
    {
        return _macros;
    }

    line_container client_instance::snapshot_full_flat() const
    {
        return _ctx->snapshot_full_flat();
    }

    relative_snapshot client_instance::snapshot_full_relative()
    {
        return _ctx->snapshot_full_relative();
    }

    relative_snapshot client_instance::snapshot_diff_relative()
    {
        return _ctx->snapshot_diff_relative();
    }

    lua_context* client_instance::get_lua_context()
    {
        return _lua_ctx.get();
    }

    void client_instance::cleanup_clickable_frames()
    {
        auto& children = _ctx->frames();
        vector<frame*> pending_deletion;
        for(auto& entry : _clickable_frames)
        {
            frame* fptr = entry.first;
            if(children.count(fptr) == 0)
            {
                pending_deletion.push_back(fptr);
            }
        }
        for(frame* fptr : pending_deletion)
        {
            _clickable_frames.erase(fptr);
        }
    }
}