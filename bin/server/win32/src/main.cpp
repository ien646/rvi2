#include <iostream>
#include <string>
#include <sstream>
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

    //auto cmds = rt.get_update_commands(cid);
    auto status = rt.get_diff_snapshot(cid);
    
    //std::cout << std::ios_base::hex;
    //for (auto& c : cmds)
    //{
    //    std::stringstream data_txt;
    //    for(auto b : c)
    //    {
    //        data_txt << +b;
    //    }
    //    std::cout << "[CMD]: " << data_txt.str() << std::endl;
    //}

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