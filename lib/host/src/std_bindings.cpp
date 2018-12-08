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
        expect_argc(args, 5 + 1);

        std::string text = args[0];
        float fontsz_x = std::stof(args[1]);
        float fontsz_y = std::stof(args[2]);
        float fontsep_x = std::stof(args[3]);
        float fontsep_y = std::stof(args[4]);
        float margin_x = std::stof(args[5]);
        float margin_y = std::stof(args[6]);
        std::string calling_frame = args[7];

        std::string buff = { 0, 0, 0 };
        rvi::vector2 curPos(margin_x, margin_y);
        int rid = std::rand();

        auto& ctx = c_inst.context;
        frame* save_fptr = ctx.selected_frame();
        frame* calling_fptr = ctx.find_frame(calling_frame);
        ctx.select_frame(calling_fptr);

        for (auto& ch : text)
        {
            buff[0] = buff[1];
            buff[1] = buff[2];
            buff[2] = ch;
            std::string defn = "$ss";
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
            
            ctx.select_frame(std::to_string(rid++) + (ch));
            ctx.set_position(curPos);
            ctx.set_scale(rvi::vector2(fontsz_x, fontsz_y));
            ctx.set_transform_scale_abs(true);
            c_inst.exec_definition(defn);
            ctx.release_frame();

            curPos.offset_in_place(rvi::vector2(fontsz_x + fontsep_x, fontsep_y));
        }

        ctx.select_frame(save_fptr);
    }

    void std_bindings::box_border(client_instance& c_inst, const arglist_t& args)
    {
        auto& ctx = c_inst.context;
        ctx.select_frame("__STD_BOX_BORDER");
        ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
        ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
        ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
        ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        ctx.release_frame();
    }

    void std_bindings::init_std_bindings(client_instance& c_inst)
    {
        c_inst.data.bindings.emplace("print", &std_bindings::print);
        c_inst.data.bindings.emplace("box_border", &std_bindings::box_border);
    }
}