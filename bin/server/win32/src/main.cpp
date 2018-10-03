#include <iostream>
#include <string>
#include <sstream>
#include <runtime.hpp>

int main()
{
    rvi::host::runtime rt;
    rvi::host::client_id cid = rt.create_client();

    std::stringstream pr;
    pr  << "select_frame:child;"
        << "draw_line:0.5,0.5,1.0,1.0;"
        << "draw_line:0.5,0.5,1.0,1.0;"
        << "release_frame:_;";

    rt.start_client(cid, pr);
    
    std::cout << cid;
    std::cin >> cid;
    return cid;
}