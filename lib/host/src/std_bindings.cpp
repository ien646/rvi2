#include "std_bindings.hpp"

#include <algorithm>

namespace rvi
{
    static void expect_argc(const arglist_t& args, size_t count)
    {
        rvi_assert(
            args.size() >= count,
            "Expected argument count of " 
                + std::to_string(count) 
                + "; Actual arg count: "
                + std::to_string(args.size())
        );
    }

    void std_bindings::print(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 1 + 1);
        const std::string& text = args[0];
        const std::string& cframe = args[1];

        std_bindings::_print(
            c_inst, 
            cframe,
            text,
            DEF_FONT_SZ, 
            DEF_FONT_SZ,
            DEF_FONT_HSEP,
            0.0F,
            DEF_FONT_MARGIN,
            DEF_FONT_MARGIN);
    }

    void std_bindings::printw(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 1 + 1);
        const std::string& text = args[0];
        const std::string& cframe = args[1];

        std_bindings::_printw(
            c_inst, 
            cframe,
            text,
            DEF_FONT_SZ, 
            DEF_FONT_SZ,
            DEF_FONT_HSEP,
            0.0F,
            DEF_FONT_MARGIN,
            DEF_FONT_MARGIN,
            DEF_FONT_WRAP_SEP_CH,
            DEF_FONT_WRAP_LINE_VSEP
        );
    }

    void std_bindings::printx(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 1 + 1); // Min 1 arg required, rest are optional
        const std::string& text = args[0];
        
        float font_sz = args.size() > 2 ? std::stof(args[1]) : DEF_FONT_SZ;
        float font_sep = args.size() > 3 ? std::stof(args[2]) : DEF_FONT_HSEP;
        float font_margin = args.size() > 4 ? std::stof(args[3]) : DEF_FONT_MARGIN;

        const std::string& cframe = args.back();

        std_bindings::_print(
            c_inst,
            cframe,
            text,
            font_sz,
            font_sz,
            font_sep,
            0.0F,
            font_margin,
            font_margin
        );
    }

    void std_bindings::printwx(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 1 + 1); // Min 1 arg required, rest are optional
        const std::string& text = args[0];
        
        float font_sz           = args.size() > 2 ? std::stof(args[1]) : DEF_FONT_SZ;
        float font_sep          = args.size() > 3 ? std::stof(args[2]) : DEF_FONT_HSEP;
        float font_margin       = args.size() > 4 ? std::stof(args[3]) : DEF_FONT_MARGIN;
        float wrap_v_sep        = args.size() > 5 ? std::stof(args[4]) : DEF_FONT_WRAP_LINE_VSEP;

        const std::string& cframe = args.back();

        std_bindings::_printw(
            c_inst, 
            cframe,
            text,
            font_sz, 
            font_sz,
            font_sep,
            0.0F,
            font_margin,
            font_margin,
            DEF_FONT_WRAP_SEP_CH,
            wrap_v_sep
        );
    }

    void std_bindings::printc(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 1 + 1); // Min 1 arg required, rest are optional
        const std::string& text = args[0];

        float font_sz_h       = args.size() > 2 ? std::stof(args[1]) : DEF_FONT_SZ;
        float font_sz_v       = args.size() > 3 ? std::stof(args[2]) : DEF_FONT_SZ;
        float font_sep_h      = args.size() > 4 ? std::stof(args[3]) : DEF_FONT_HSEP;
        float font_sep_v      = args.size() > 5 ? std::stof(args[4]) : 0.0F;
        float font_margin_h   = args.size() > 6 ? std::stof(args[5]) : DEF_FONT_MARGIN;
        float font_margin_v   = args.size() > 7 ? std::stof(args[6]) : DEF_FONT_MARGIN;

        const std::string& cframe = args.back();

        std_bindings::_print(
            c_inst,
            cframe,
            text,
            font_sz_h,
            font_sz_v,
            font_sep_h,
            font_sep_v,
            font_margin_h,
            font_margin_v
        );
    }

    void std_bindings::printcw(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 1 + 1); // Min 1 arg required, rest are optional
        const std::string& text = args[0];

        float font_sz_h       = args.size() > 2 ? std::stof(args[1]) : DEF_FONT_SZ;
        float font_sz_v       = args.size() > 3 ? std::stof(args[2]) : DEF_FONT_SZ;
        float font_sep_h      = args.size() > 4 ? std::stof(args[3]) : DEF_FONT_HSEP;
        float font_sep_v      = args.size() > 5 ? std::stof(args[4]) : 0.0F;
        float font_margin_h   = args.size() > 6 ? std::stof(args[5]) : DEF_FONT_MARGIN;
        float font_margin_v   = args.size() > 7 ? std::stof(args[6]) : DEF_FONT_MARGIN;
        char  sep_char        = args.size() > 8 ? args[7][0] : DEF_FONT_WRAP_SEP_CH;
        float wrap_v_sep      = args.size() > 9 ? std::stof(args[8]) : DEF_FONT_WRAP_LINE_VSEP;

        const std::string& cframe = args.back();

        std_bindings::_printw(
            c_inst,
            cframe,
            text,
            font_sz_h,
            font_sz_v,
            font_sep_h,
            font_sep_v,
            font_margin_h,
            font_margin_v,
            sep_char,
            wrap_v_sep
        );
    }

    extern void std_bindings::_print(
        client_instance& c_inst,
        const std::string& calling_frame,
        const std::string& text,
        float font_sz_h,
        float font_sz_v,
        float font_sep_h,
        float font_sep_v,
        float font_margin_h,
        float font_margin_v)
    {
        std::string buff = { 0, 0, 0 };
        auto& ctx = c_inst.context;
        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);

        vector2 offset(font_margin_h, font_margin_v);

        ctx.select_frame(calling_fptr);
        int idx = 0;
        for (auto& ch : text)
        {
            buff[0] = buff[1];
            buff[1] = buff[2];
            buff[2] = ch;

            std::string defn;
            if (buff[0] == '$')
            {
                defn = buff;
            }
            else if (buff[1] == '$' || buff[2] == '$')
            {
                continue;
            }
            else
            {
                defn = std::string(1, ch);
            }
            
            ctx.select_frame("char_" + std::to_string(idx));
            {
                ctx.set_scale(vector2(font_sz_h, font_sz_v));
                ctx.set_transform_scale_abs(true);
                ctx.set_position(offset);
                c_inst.exec_macro(defn);
            }
            ctx.release_frame();

            offset += vector2(font_sz_h + font_sep_h, font_sep_v);
            ++idx;
        }
        ctx.select_frame(save_fptr);
    }

    extern void std_bindings::_printw(
        client_instance& c_inst,
        const std::string& calling_frame,
        const std::string& text,
        float font_sz_h,
        float font_sz_v,
        float font_sep_h,
        float font_sep_v,
        float font_margin_h,
        float font_margin_v,
        char wrap_sep_char,
        float wrap_vsep)
    {
        std::string buff = { 0, 0, 0 };
        auto& ctx = c_inst.context;
        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);

        float x_max_sz = calling_fptr->get_absolute_transform().scale.x;
        float y_max_sz = calling_fptr->get_absolute_transform().scale.y;

        vector2 offset(
            font_margin_h,
            (y_max_sz - font_sz_v) - font_margin_v
        );

        bool first = true;

        ctx.select_frame(calling_fptr);
        std::stringstream tstr(text);
        std::string line;
        int idx = 0;
        while(std::getline(tstr, line, wrap_sep_char))
        {
            line += wrap_sep_char;
            if(!first)
            {
                float finalPos = offset.x + 
                    (line.size() * font_sz_h) + 
                    ((line.size() - 1) * font_sep_h);

                if(finalPos > x_max_sz)
                {
                    offset.x = font_margin_h;
                    offset.y -= (font_sz_v + wrap_vsep);
                }
            }
            first = false;
            for (auto& ch : line)
            {
                buff[0] = buff[1];
                buff[1] = buff[2];
                buff[2] = ch;

                std::string defn;
                if (buff[0] == '$')
                {
                    defn = buff;
                }
                else if (buff[1] == '$' || buff[2] == '$')
                {
                    continue;
                }
                else
                {
                    defn = std::string(1, ch);
                }
                
                ctx.select_frame("char_" + std::to_string(idx));
                {
                    ctx.set_scale(vector2(font_sz_h, font_sz_v));
                    ctx.set_transform_scale_abs(true);
                    ctx.set_position(offset);
                    c_inst.exec_macro(defn);
                }
                ctx.release_frame();

                offset += vector2(font_sz_h + font_sep_h, font_sep_v);
                ++idx;
            }
        }
        ctx.select_frame(save_fptr);
    }

    void std_bindings::box_border(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 0 + 1);

        auto& calling_frame = args.back();
        auto& ctx = c_inst.context;

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_BOX_BORDER");
        {
            ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
            ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
            ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
            ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        }
        ctx.select_frame(save_fptr);
    }

    void std_bindings::box_border_rgba(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 4 + 1);
        auto& calling_frame = args.back();
        auto& ctx = c_inst.context;

        uint8_t r = static_cast<uint8_t>(std::min(std::stoi(args[0]), 255));
        uint8_t g = static_cast<uint8_t>(std::min(std::stoi(args[1]), 255));
        uint8_t b = static_cast<uint8_t>(std::min(std::stoi(args[2]), 255));
        uint8_t a = 255;
        if(args.size() > 3)
        {
            a = static_cast<uint8_t>(std::min(std::stoi(args[3]), 255));
        }
        color_rgba border_color = color_rgba(r, g, b, a);

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);
        color_rgba save_color = ctx.current_color();

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_BOX_BORDER");
        {
            ctx.set_color(border_color);
            ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
            ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
            ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
            ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        }
        ctx.set_color(save_color);
        ctx.select_frame(save_fptr);
    }

    void std_bindings::cross(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 0 + 1);

        auto& calling_frame = args.back();
        auto& ctx = c_inst.context;

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_CROSS");
        {
            ctx.draw_line(vector2(0, 0), vector2(1, 1)); //  /
            ctx.draw_line(vector2(0, 1), vector2(1, 0)); //  X
        }
        ctx.select_frame(save_fptr);
    }

    void std_bindings::cross_rgba(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 4 + 1);
        auto& calling_frame = args[0];
        auto& ctx = c_inst.context;

        uint8_t r = static_cast<uint8_t>(std::min(std::stoi(args[0]), 255));
        uint8_t g = static_cast<uint8_t>(std::min(std::stoi(args[1]), 255));
        uint8_t b = static_cast<uint8_t>(std::min(std::stoi(args[2]), 255));
        uint8_t a = 255;
        if(args.size() > 3)
        {
            a = static_cast<uint8_t>(std::min(std::stoi(args[3]), 255));
        }
        color_rgba cross_color = color_rgba(r, g, b, a);

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);
        color_rgba save_color = ctx.current_color();

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_CROSS");
        {
            ctx.set_color(cross_color);
            ctx.draw_line(vector2(0, 0), vector2(1, 1)); //  /
            ctx.draw_line(vector2(0, 1), vector2(1, 0)); //  X
            ctx.set_color(save_color);
        }
        ctx.select_frame(save_fptr);
    }

    void std_bindings::grid_fill_abs(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 0 + 1);

        float grid_cell_sz = args.size() > 1 ? std::stof(args[0]) : DEF_GRIDFILL_SEP;

        const std::string& calling_frame = args.back();
        auto& ctx = c_inst.context;

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);

        float x_step = 1.0F / grid_cell_sz;
        float y_step = 1.0F / grid_cell_sz;

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_GRID_FILL");
        {
            for(float x = 0; x <= 1.0F; x += x_step)
            {
                ctx.draw_line(vector2(x, 0), vector2(x, 1));
            }

            for(float y = 0; y <= 1.0F; y += y_step)
            {
                ctx.draw_line(vector2(y, 0), vector2(y, 1));
            }
        }
        ctx.select_frame(save_fptr);
    }

    void std_bindings::grid_fill_abs_rgba(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 4 + 1);

        float grid_cell_sz = args.size() > 1 ? std::stof(args[0]) : DEF_GRIDFILL_SEP;

        const std::string& calling_frame = args.back();
        auto& ctx = c_inst.context;

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);
        color_rgba save_color = ctx.current_color();

        uint8_t r = static_cast<uint8_t>(std::min(std::stoi(args[0]), 255));
        uint8_t g = static_cast<uint8_t>(std::min(std::stoi(args[1]), 255));
        uint8_t b = static_cast<uint8_t>(std::min(std::stoi(args[2]), 255));
        uint8_t a = 255;
        if(args.size() > 3)
        {
            a = static_cast<uint8_t>(std::min(std::stoi(args[3]), 255));
        }
        color_rgba grid_color = color_rgba(r, g, b, a);

        float x_step = 1.0F / grid_cell_sz;
        float y_step = 1.0F / grid_cell_sz;

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_GRID_FILL");
        {
            ctx.set_color(grid_color);

            for(float x = 0; x <= 1.0F; x += x_step)
            {
                ctx.draw_line(vector2(x, 0), vector2(x, 1));
            }

            for(float y = 0; y <= 1.0F; y += y_step)
            {
                ctx.draw_line(vector2(y, 0), vector2(y, 1));
            }
        }
        ctx.select_frame(save_fptr);
        ctx.set_color(save_color);
    }

    void std_bindings::grid_fill_rlt(client_instance& c_inst, const arglist_t& args)
    {
        throw std::logic_error("Not implemented");
    }

    void std_bindings::grid_fill_rlt_rgba(client_instance& c_inst, const arglist_t& args)
    {
        throw std::logic_error("Not implemented");
    }

    void std_bindings::clear_context(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 0 + 1);
        auto& ctx = c_inst.context;
        while(ctx.release_frame()) { continue; }
        ctx.clear_children();
    }

    void std_bindings::init_std_bindings(client_instance& c_inst)
    {
        c_inst.create_binding("print", &std_bindings::print);
        c_inst.create_binding("printw", &std_bindings::printw);
        c_inst.create_binding("printx", &std_bindings::printx);
        c_inst.create_binding("printwx", &std_bindings::printwx);
        c_inst.create_binding("printc", &std_bindings::printc);
        c_inst.create_binding("printwc", &std_bindings::printcw);

        c_inst.create_binding("box_border", &std_bindings::box_border);
        c_inst.create_binding("box_border_rgba", &std_bindings::box_border);

        c_inst.create_binding("cross", &std_bindings::cross);
        c_inst.create_binding("cross_rgba", &std_bindings::cross_rgba);

        c_inst.create_binding("grid_fill_abs", &std_bindings::grid_fill_abs);
        c_inst.create_binding("grid_fill_abs_rgba", &std_bindings::grid_fill_abs_rgba);

        c_inst.create_binding("clear_context", &std_bindings::clear_context);
    }
}