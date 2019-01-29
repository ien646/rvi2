#pragma once

#include <rvi/client_context.hpp>
#include <rvi/client_instance.hpp>
#include <sol.hpp>

namespace rvi
{
    class lua_context
    {
    private:
        client_instance& _inst;
        client_context* _inst_ctx;
        sol::state _lua;

    public:
        lua_context(client_instance& inst)
            : _inst(inst)
            , _inst_ctx(inst.get_context())
        { 
            init_client_instance_interface();
        }

    private:
        init_client_instance_interface()
        {
            _lua.set_function("select_frame",  [&](std::string&& name)
            {
                _inst_ctx->select_frame(name);
            });

            _lua.set_function("delete_frame",  [&](std::string&& name)
            { 
                _inst_ctx->delete_frame(name);
            });

            _lua.set_function("release_frame", [&]{ _inst_ctx->release_frame(); });

            _lua.set_function("draw_line", [&](float fx, float fy, float tx, float ty)
            {
                _inst_ctx->draw_line(vector2(fx, fy), vector2(tx, ty));
            });

            _lua.set_function("set_color", [&](int r, int g, int b, int a)
            {
                _inst_ctx->set_color(color_rgba(
                    static_cast<u8>(r),
                    static_cast<u8>(g),
                    static_cast<u8>(b),
                    static_cast<u8>(a)
                ));
            });

            _lua.set_function("set_position", [&](float x, float y)
            {
                _inst_ctx->set_position(vector2(x, y));
            });

            _lua.set_function("set_scale", [&](float x, float y)
            {
                _inst_ctx->set_scale(vector2(x, y));
            });

            _lua.set_function("set_rotation", [&](float angle)
            {
                _inst_ctx->set_rotation(angle);
            });

            _lua.set_function("define", [&](const std::string& name, sol::variadic_args args)
            {
                if(_macros.count(name) > 0)
                {
                    _macros.remove(name);
                }

                _macros.emplace(name, std::vector<std::string>());
                for(auto v : args)
                {
                    _macros[name].push_back(v.as<std::string>());
                }
            });

            _lua.set_function("undefine", [&](const std::string& name)
            {
                if(_macros.count(name) > 0)
                {
                    _macros.remove(name);
                }
            });

            
        }
    };
}
