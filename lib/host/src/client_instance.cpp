#include <rvi/client_instance.hpp>

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
        std::vector<int> pending_deletion_idx;
        for(size_t i = 0; i < _clickable_frames.size(); ++i)
        {
            frame* fptr = _clickable_frames[i];
            if(children.count(fptr) > 0)
            {
                pending_deletion_idx.push_back(i);
            }
        }
        for(int i : pending_deletion_idx)
        {
            _clickable_frames.erase(_clickable_frames.begin() + i);
        }
    }
}