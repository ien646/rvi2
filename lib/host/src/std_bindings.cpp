#include "std_bindings.hpp"

namespace rvi::host
{
    void std_bindings::print(client_context& ctx, const std::vector<std::string>& args)
    {
        std::string text = args[0];
        float fontsz_x = std::stof(args[1]);
        float fontsz_y = std::stof(args[2]);
        float fontsep_x = std::stof(args[3]);
        float fontsep_y = std::stof(args[4]);

        std::string buff = { 0, 0, 0 };
        rvi::vector2 curPos;

        int rid = std::rand();

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
            ctx.execute_definition(defn);
            ctx.release_frame();

            curPos.offset_in_place(rvi::vector2(fontsz_x + fontsep_x, fontsep_y));
        }
    }
}