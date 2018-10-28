#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <deserializer.hpp>
#include <runtime.hpp>

#include "data_reader.hpp"

static void draw_text(rvi::client_context& ctx, const std::vector<std::string>& args)
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

        curPos.offset_in_place(rvi::vector2(fontsep_x, fontsep_y));
    }
}

int main()
{
    rvi::host::runtime rt;
    rvi::host::cid_t cid = rt.create_client();

    std::ifstream ifs("data/main.rpf");

    std::stringstream ss;
    ss << ifs.rdbuf();

    rt.create_binding("draw_text", [](rvi::client_context& ctx, const std::vector<std::string>& args)
    {
        draw_text(ctx, args);
    });
    
    rt.start_client(cid, ss);

    auto cmds = rt.get_update_commands(cid);
    
    std::cout << std::endl;
    for (auto& c : cmds)
    {        
        switch(static_cast<rvi::serialization::cmd_header>(c[0]))
        {
            case rvi::serialization::cmd_header::SELECT_FRAME:
            {
                std::cout   << "[SELECT_FRAME]:" 
                            << rvi::serialization::deserializer::select_frame(c, 1)
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::RELEASE_FRAME:
            {
                std::cout   << "[RELEASE_FRAME]"
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::DELETE_FRAME:
            {
                std::cout   << "[DELETE_FRAME]:" 
                            << rvi::serialization::deserializer::delete_frame(c, 1)
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::DRAW_LINE:
            {
                std::cout   << "[DRAW_LINE]:"
                            << rvi::serialization::deserializer::draw_line(c, 1).to_string()
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::SET_TRANSFORM:
            {
                std::cout   << "[SET_TRANSFORM]:"
                            << rvi::serialization::deserializer::set_transform(c, 1).to_string()
                            << std::endl;
                break;
            }
        }
    }

    std::cout << cid;
    std::cin >> cid;
    return cid;
}