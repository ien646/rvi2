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

        _lua.set_function("distort", [&](
            float ul_x, float ul_y,
            float ur_x, float ur_y,
            float ll_x, float ll_y,
            float lr_x, float lr_y)
        {
            _inst.get_context()->selected_frame()->distort(
                vector2(ul_x, ul_y),
                vector2(ur_x, ur_y),
                vector2(ll_x, ll_y),
                vector2(lr_x, lr_y)
            );
        });
    }

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
            "mul",          (vector2(vector2::*)(float))(&vector2::operator*),
            "div",          (vector2(vector2::*)(float))(&vector2::operator/),
            "cross",        (vector2(vector2::*)(vector2))(&vector2::operator*),
            "normalized",   &vector2::normalized
        );

        /*-- print_settings --*/
        _lua.new_usertype<print_settings>(
            "print_settings",   sol::constructors<print_settings()>(),
            "font_size" ,       &print_settings::font_size,
            "font_sep",         &print_settings::font_sep,
            "font_margin",      &print_settings::font_margin,
            "wrap_sep_char",    &print_settings::wrap_sep_char,
            "wrap_vsep",        &print_settings::wrap_vsep
        );
    }

    void lua_context::init_std_library()
    {
        using rvi::standard::print_settings;
        // ====================================================================
        // -- rprint ----------------------------------------------------------
        // ====================================================================

        _lua.set_function("printr", [&](const std::string text, print_settings p_set)
        {
            rvi::standard::print(_inst, _inst_ctx->selected_frame(), text, p_set);
        });

        // ====================================================================
        // -- rprint_wrap -----------------------------------------------------
        // ====================================================================

        _lua.set_function("printr_wrap", [&](const std::string& text, print_settings p_set)
        {
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