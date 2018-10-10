#include <iostream>
#include <string>
#include <sstream>

#include <deserializer.hpp>
#include <runtime.hpp>

int main()
{
    rvi::host::runtime rt;
    rvi::host::cid_t cid = rt.create_client();

    std::stringstream pr;
    pr << "select_frame:child;"
        << "set_scale:0.5,0.5;"
        << "draw_line:0.5,0.5,1.0,1.0;"
        << "draw_line:0.6,0.75,1.0,1.0;"
        << "release_frame:_;"
        << "define:a,{draw_line:0.5,0.5,0.5,0.5;};"
        << "call:a;"
        << "undefine:a;";

    rt.start_client(cid, pr);

    auto cmds = rt.get_update_commands(cid);
    auto status = rt.get_diff_snapshot(cid);
    
    std::cout << std::ios_base::hex;
    for (auto& c : cmds)
    {
        switch(static_cast<rvi::serialization::cmd_header>(c[0]))
        {
            case rvi::serialization::cmd_header::SELECT_FRAME:
            {
                std::cout   << "CMD[SELECT_FRAME]:" 
                            << rvi::serialization::deserializer::select_frame(c, 1)
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::RELEASE_FRAME:
            {
                std::cout   << "CMD[RELEASE_FRAME]"
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::DELETE_FRAME:
            {
                std::cout   << "CMD[DELETE_FRAME]:" 
                            << rvi::serialization::deserializer::delete_frame(c, 1)
                            << std::endl;
                break;
            }
            case rvi::serialization::cmd_header::DRAW_LINE:
            {
                std::cout   << "CMD[DRAW_LINE]:"
                            << rvi::serialization::deserializer::draw_line(c, 1).to_string()
                            << std::endl;
                break;
            }
        }
    }

    for (auto& p : status)
    {
        std::cout << "-- FRAME : [" << p.first << "]" << std::endl;
        std::for_each(p.second.begin(), p.second.end(), [](rvi::line& l) 
        {
            std::cout << l.to_string() << std::endl;
        });
    }

    std::cout << cid;
    std::cin >> cid;
    return cid;
}