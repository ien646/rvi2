#include "std_bindings.hpp"

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
            DEF_FONT_WRAP_SEP_CH);
    }

    void std_bindings::print_ex(client_instance& c_inst, const arglist_t& args)
    {

    }

    void std_bindings::printw_ex(client_instance& c_inst, const arglist_t& args)
    {

    }

    void std_bindings::printc(client_instance& c_inst, const arglist_t& args)
    {

    }

    void std_bindings::printcw(client_instance& c_inst, const arglist_t& args)
    {
        
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

            offset += vector2(font_sz_h + font_sep_h, font_sz_v + font_sep_v);
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
        char wsep_char)
    {
        // ...
    }

    void std_bindings::box_border(client_instance& c_inst, const arglist_t& args)
    {
        expect_argc(args, 0 + 1);

        auto& calling_frame = args[0];
        auto& ctx = c_inst.context;

        frame* save_fptr = ctx.selected_frame();
        frame* calling_frame = ctx.find_frame(args[0]);

        ctx.select_frame(calling_frame);
        ctx.select_frame("__STD_BOX_BORDER");
        ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
        ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
        ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
        ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        ctx.select_frame(save_fptr);
    }

    void std_bindings::init_std_bindings(client_instance& c_inst)
    {
        c_inst.data.bindings.emplace("print", &std_bindings::print);
        c_inst.data.bindings.emplace("box_border", &std_bindings::box_border);
    }
}