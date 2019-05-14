#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include <rvi/client_context.hpp>
#include <rvi/clickable_frame_data.hpp>
#include <rvi/lua_context.hpp>

namespace rvi
{
    class runtime; //fwd
    typedef uint64_t rvi_cid_t;
    class client_instance
    {
    private:
        std::unique_ptr<client_context> _ctx;
        std::unordered_map<std::string, std::vector<std::string>> _macros;
        std::unordered_map<frame*, clickable_frame_data> _clickable_frames;
        std::unique_ptr<lua_context> _lua_ctx;
        runtime* _runtime_ptr;
        rvi_cid_t _cid;

    public:
        client_instance(runtime* rptr, rvi_cid_t cid);

        void reload();

        client_context* get_context();
        runtime* get_runtime();
        rvi_cid_t client_id();

        void define_macro(const std::string& name, const std::vector<std::string>& funs);
        void undefine_macro(const std::string& name);

        std::optional<std::reference_wrapper<std::vector<std::string>>>
        get_macro(const std::string& name);

        void exec_macro(const std::string& mname);

        void set_current_frame_clickable(const std::string& binding_name);
        void unset_current_frame_clickable();
        
        void user_click(vector2 pos);

        line_container snapshot_full_flat() const;
        relative_snapshot snapshot_full_relative();
        relative_snapshot snapshot_diff_relative();

        void run_script_file(const std::string& filepath);

        lua_context* get_lua_context();

        const std::unordered_map<std::string, std::vector<std::string>>& macros();

        void add_client_handler(const std::string& hname);

    private:
        void cleanup_clickable_frames();
    };
}