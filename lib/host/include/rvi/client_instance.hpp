#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include <rvi/client_context.hpp>

namespace rvi
{
    typedef std::function<void(client_instance&, std::vector<std::string>& args)> binding_t;
    class client_instance
    {
    private:
        std::unique_ptr<client_context> _ctx;
        std::unordered_map<std::string, std::vector<std::string>> _macros;
        std::vector<frame*> _clickable_frames;

    public:
        client_instance();

        client_context* get_context();

        void define_macro(const std::string& name, std::vector<std::string>& funs);
        std::optional<const std::vector<std::string>&> get_macro(std::string& name);

        std::vector<line> snapshot_full_flat() const;
        relative_snapshot snapshot_full_relative();
        relative_snapshot snapshot_diff_relative();

    private:
        void cleanup_clickable_frames();
    };
}