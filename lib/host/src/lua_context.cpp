#include <rvi/lua_context.hpp>

#include <rvi/client_instance.hpp>
#include <rvi/standard_library.hpp>
#include <rvi/vector2.hpp>

namespace rvi
{
    lua_context::lua_context(client_instance& inst)
        : _inst(inst)
        , _inst_ctx(inst.get_context())
    { 
        init_types();
        init_lua_interface();
        init_std_library();
    }

    void lua_context::init_lua_interface()
    {
        _lua.set_function("include", [&](const std::string& name)
        {
            _lua.script_file("data/" + name);
        });

        _lua.set_function("select_frame",  [&](const std::string& name)
        {
            _inst_ctx->select_frame(name);
        });

        _lua.set_function("delete_frame",  [&](const std::string& name)
        { 
            _inst_ctx->delete_frame(name);
        });

        _lua.set_function("release_frame", [&]{ _inst_ctx->release_frame(); });

        _lua.set_function("draw_line", [&](vector2 from, vector2 to)
        {
            _inst_ctx->draw_line(from, to);
        });

        _lua.set_function("set_color", [&](color_rgba color)
        {
            _inst_ctx->set_color(color);
        });

        _lua.set_function("set_position", [&](vector2 position)
        {
            _inst_ctx->set_position(position);
        });

        _lua.set_function("set_scale", [&](vector2 scale)
        {
            _inst_ctx->set_scale(scale);
        });

        _lua.set_function("set_rotation", [&](float angle)
        {
            _inst_ctx->set_rotation(angle);
        });

        _lua.set_function("define", [&](const std::string& name, sol::variadic_args args)
        {
            std::vector<std::string> macro_funs;
            for(auto v : args)
            {
                macro_funs.push_back(v.as<std::string>());
            }
            _inst.define_macro(name, macro_funs);
        });

        _lua.set_function("undefine", [&](const std::string& name)
        {
            _inst.undefine_macro(name);
        });

        _lua.set_function("macro", [&](const std::string& name)
        {
            _inst.exec_macro(name);
        });

        _lua.set_function("set_clickable", [&](const std::string& binding_name)
        {
            _inst.set_current_frame_clickable(binding_name);
        });

        _lua.set_function("unset_clickable", [&]
        {
            _inst.unset_current_frame_clickable();
        });

        _lua.set_function("distort", [&](vector2 ul, vector2 ur, vector2 ll, vector2 lr)
        {
            _inst.get_context()->selected_frame()->distort(ul, ur, ll, lr);
        });
    }

#define RVI_VEC2_MULDIV_OVERLOAD(fp) \
    static_cast<vector2(vector2::*)(float) const noexcept>(fp)

    void lua_context::init_types()
    {
        using rvi::standard::print_settings;

        /*-- vector2 --*/
        _lua.new_usertype<vector2>(
            "vector2",      sol::constructors<vector2(), vector2(float, float)>(),
            "x",            &vector2::x,
            "y",            &vector2::y,
            "add",          &vector2::operator+,
            "sub",          &vector2::operator-,
            "mul",          RVI_VEC2_MULDIV_OVERLOAD(&vector2::operator*),
            "div",          RVI_VEC2_MULDIV_OVERLOAD(&vector2::operator/),
            "cross",        &vector2::cross_product,
            "normalized",   &vector2::normalized
        );

        _lua.set_function("vec2", [](float x, float y)
        {
            return vector2(x, y);
        });

        /*-- print_settings --*/
        _lua.new_usertype<print_settings>(
            "print_settings",   sol::constructors<print_settings()>(),
            "font_size" ,       &print_settings::font_size,
            "font_sep",         &print_settings::font_sep,
            "font_margin",      &print_settings::font_margin,
            "wrap_sep_char",    &print_settings::wrap_sep_char,
            "wrap_vsep",        &print_settings::wrap_vsep
        );

        _lua.new_usertype<color_rgba>(
            "color_rgba", sol::constructors<color_rgba(), color_rgba(u8, u8, u8, u8)>(),
            "rgba", &color_rgba::rgba
        );
    }

    void lua_context::init_std_library()
    {
        using rvi::standard::print_settings;

        _lua.set_function("printr", [&](const std::string text, sol::variadic_args args)
        {
            print_settings p_set;
            if(args.size() >= 1)
            {
                p_set = args.get<print_settings>(0);
            }
            rvi::standard::print(_inst, _inst_ctx->selected_frame(), text, p_set);
        });

        _lua.set_function("printr_wrap", [&](const std::string& text, sol::variadic_args args)
        {
            print_settings p_set;
            if(args.size() >= 1)
            {
                p_set = args.get<print_settings>(0);
            }
            rvi::standard::printw(_inst, _inst_ctx->selected_frame(), text, p_set);
        });

        _lua.set_function("box_border", [&]
        {
            rvi::standard::box_border(*_inst_ctx);
        });

        _lua.set_function("grid_fill", [&](float x_step, float y_step)
        {
            rvi::standard::grid_fill(*_inst_ctx, x_step, y_step);
        });

        _lua.set_function("grid_fill_rlt", [&](int x_count, int y_count)
        {
            float x_sz = 1.0F / x_count;
            float y_sz = 1.0F / y_count;
            rvi::standard::grid_fill(*_inst_ctx, x_sz, y_sz);
        });

        _lua.set_function("stitch_fill", [&](float step_sz)
        {
            rvi::standard::stitch_fill(*_inst_ctx, step_sz);
        });

        _lua.set_function("stitch_fill_rlt", [&](int step_count)
        {
            float step_sz = 1.0F / step_count;
            rvi::standard::stitch_fill(*_inst_ctx, step_sz);
        });

        _lua.set_function("horizontal_fill", [&](float step_sz)
        {
            rvi::standard::horizontal_fill(*_inst_ctx, step_sz);
        });

        _lua.set_function("horizontal_fill_rlt", [&](int step_count)
        {
            float step_sz = 1.0F / step_count;
            rvi::standard::horizontal_fill(*_inst_ctx, step_sz);
        });

        _lua.set_function("vertical_fill", [&](float step_sz)
        {
            rvi::standard::vertical_fill(*_inst_ctx, step_sz);
        });

        _lua.set_function("horizontal_fill", [&](int step_count)
        {
            float step_sz = 1.0F / step_count;
            rvi::standard::vertical_fill(*_inst_ctx, step_sz);
        });
    }

    void lua_context::exec_script(const std::string& scr)
    {
        _lua.script(scr);
    }

    void lua_context::exec_script_file(const std::string& scr_filepath)
    {
        _lua.script_file(scr_filepath);
    }
}