#include <rvi/lua_context.hpp>

#include <rvi/client_instance.hpp>
#include <rvi/standard_library.hpp>

namespace rvi
{
    lua_context::lua_context(client_instance& inst)
        : _inst(inst)
        , _inst_ctx(inst.get_context())
    { 
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
    }

    void lua_context::init_std_library()
    {
        // ====================================================================
        // -- rprint ----------------------------------------------------------
        // ====================================================================

        _lua.set_function("rprint", 
        [&](const std::string text, sol::variadic_args vargs)
        {
            float font_sz_h     = rvi::standard::DEFAULT_FONT_SZ_H;
            float font_sz_v     = rvi::standard::DEFAULT_FONT_SZ_V;
            float font_sep_h    = rvi::standard::DEFAULT_FONT_SEP_H;
            float font_sep_v    = rvi::standard::DEFAULT_FONT_SEP_V;
            float font_margin_h = rvi::standard::DEFAULT_FONT_MARGIN_H;
            float font_margin_v = rvi::standard::DEFAULT_FONT_MARGIN_V;

            switch(vargs.size())
            {
                default: [[fallthrough]];
                case 6: font_margin_v = vargs[5].as<float>(); [[fallthrough]];
                case 5: font_margin_h = vargs[4].as<float>(); [[fallthrough]];
                case 4: font_sep_v    = vargs[3].as<float>(); [[fallthrough]];
                case 3: font_sep_h    = vargs[2].as<float>(); [[fallthrough]];
                case 2: font_sz_v     = vargs[1].as<float>(); [[fallthrough]];
                case 1: font_sz_h     = vargs[0].as<float>(); [[fallthrough]];
                case 0: break;
            }

            rvi::standard::print(
                _inst,
                _inst_ctx->selected_frame(),
                text,
                font_sz_h,
                font_sz_v,
                font_sep_h,
                font_sep_v,
                font_margin_h,
                font_margin_v
            );
        });

        // ====================================================================
        // -- rprint_wrap -----------------------------------------------------
        // ====================================================================

        _lua.set_function("rprint_wrap", 
        [&](const std::string& text, sol::variadic_args vargs)
        {
            float font_sz_h     = rvi::standard::DEFAULT_FONT_SZ_H;
            float font_sz_v     = rvi::standard::DEFAULT_FONT_SZ_V;
            float font_sep_h    = rvi::standard::DEFAULT_FONT_SEP_H;
            float font_sep_v    = rvi::standard::DEFAULT_FONT_SEP_V;
            float font_margin_h = rvi::standard::DEFAULT_FONT_MARGIN_H;
            float font_margin_v = rvi::standard::DEFAULT_FONT_MARGIN_V;
            char  wrap_sep_ch   = rvi::standard::DEFAULT_WRAP_SEP_CHAR;
            float wrap_sep_v    = rvi::standard::DEFAULT_WRAP_LNSEP_V;

            switch(vargs.size())
            {
                default: [[fallthrough]];
                case 8: wrap_sep_v    = vargs[7].as<float>(); [[fallthrough]];
                case 7: wrap_sep_ch   = vargs[6].as<char>();  [[fallthrough]];
                case 6: font_margin_v = vargs[5].as<float>(); [[fallthrough]];
                case 5: font_margin_h = vargs[4].as<float>(); [[fallthrough]];
                case 4: font_sep_v    = vargs[3].as<float>(); [[fallthrough]];
                case 3: font_sep_h    = vargs[2].as<float>(); [[fallthrough]];
                case 2: font_sz_v     = vargs[1].as<float>(); [[fallthrough]];
                case 1: font_sz_h     = vargs[0].as<float>(); [[fallthrough]];
                case 0: break;
            }

            rvi::standard::printw(
                _inst,
                _inst_ctx->selected_frame(),
                text,
                font_sz_h,
                font_sz_v,
                font_sep_h,
                font_sep_v,
                font_margin_h,
                font_margin_v,
                wrap_sep_ch,
                wrap_sep_v
            );
        });

        _lua.set_function("rbox_border", [&]
        {
            rvi::standard::box_border(*_inst_ctx);
        });

        _lua.set_function("rgrid_fill", [&](float x_step, float y_step)
        {
            rvi::standard::grid_fill(*_inst_ctx, x_step, y_step);
        });

        _lua.set_function("rgrid_fill_rel", [&](int x_count, int y_count)
        {
            float x_sz = 1.0F / x_count;
            float y_sz = 1.0F / y_count;
            rvi::standard::grid_fill(*_inst_ctx, x_sz, y_sz);
        });

        _lua.set_function("rstitch_fill", [&](float step_sz)
        {
            rvi::standard::stitch_fill(*_inst_ctx, step_sz);
        });

        _lua.set_function("rstitch_fill_rel", [&](int step_count)
        {
            float step_sz = 1.0F / step_count;
            rvi::standard::stitch_fill(*_inst_ctx, step_sz);
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