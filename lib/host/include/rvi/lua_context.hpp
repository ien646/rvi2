#pragma once

#include <rvi/client_context.hpp>
#include <sol.hpp>

namespace rvi
{
    class client_instance;
    
    class lua_context
    {
    private:
        client_instance* _inst;
        client_context* _inst_ctx;
        sol::state _lua;

    public:
        lua_context(client_instance* inst);

        void exec_script(const std::string& scr);
        void exec_script_file(const std::string& scr_filepath);

        sol::state* get_lua_state();

    private:
        void init_lua_interface();
        void init_types();
        void init_std_library();
    };
}
