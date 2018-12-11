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
                c_inst.exec_definition(defn);
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
                float finalPos = offset.x + (line.size() * font_sz_h) + ((line.size() - 1) * font_sep_h);
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
                    c_inst.exec_definition(defn);
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

        auto& calling_frame = args[0];
        auto& ctx = c_inst.context;

        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(args[0]);

        ctx.select_frame(calling_fptr);
        ctx.select_frame("__STD_BOX_BORDER");
        ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
        ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
        ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
        ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        ctx.select_frame(save_fptr);
    }

    void std_bindings::init_std_bindings(client_instance& c_inst)
    {
        c_inst.data.bindings.emplace("print",       &std_bindings::print);
        c_inst.data.bindings.emplace("printw",      &std_bindings::printw);
        c_inst.data.bindings.emplace("printx",      &std_bindings::printx);
        c_inst.data.bindings.emplace("printwx",     &std_bindings::printwx);
        c_inst.data.bindings.emplace("printc",      &std_bindings::printc);
        c_inst.data.bindings.emplace("printwc",     &std_bindings::printcw);
        c_inst.data.bindings.emplace("box_border",  &std_bindings::box_border);
    }
}