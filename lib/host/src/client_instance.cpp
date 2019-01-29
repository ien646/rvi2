#include <rvi/client_instance.hpp>

#include <map>

namespace rvi
{
    client_instance::client_instance()
    {
        _ctx = std::make_unique<client_context>();
    }

    client_context* client_instance::get_context()
    {
        return _ctx.get();
    }

    void client_instance::define_macro(const std::string& name, const std::vector<std::string>& funs)
    {
        _macros.emplace(name, funs);
    }

    std::optional<const std::vector<std::string>&> client_instance::get_macro(const std::string& name)
    {
        if(_macros.count(name) > 0)
        {
            return std::optional<const std::vector<std::string>&>(_macros[name]);
        }
        return std::optional<const std::vector<std::string>&>(std::nullopt);
    }

    void client_instance::set_current_frame_clickable(clickable_frame_data::click_call_t call)
    {
        frame* fptr = _ctx->selected_frame();
        clickable_frame_data fdata(fptr, call);
        _clickable_frames.emplace(fptr, fdata);
    }

    void client_instance::user_click(vector2 pos)
    {
        auto& ctx_frames = _ctx->frames();
        std::map<uint64_t, frame*> hits;
        std::vector<frame*> pending_delete;

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

        // Hit frame with the latest uid (added last)
        auto pair = *(hits.rbegin()); // std::map keys are ordered
        _clickable_frames[pair.second].click_call(*this);
    }

    std::vector<line> client_instance::snapshot_full_flat() const
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

    void client_instance::cleanup_clickable_frames()
    {
        auto& children = _ctx->frames();
        std::vector<frame*> pending_deletion;
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