#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <deserializer.hpp>
#include <runtime.hpp>

#include "data_reader.hpp"

int main()
{
    rvi::host::runtime rt;
    rvi::host::cid_t cid = rt.create_client();

    auto files = data_reader::enum_data_files("data", true);
    std::vector<std::string> files_text;

    for(auto& f : files.runtime_files)
    {        
        std::ifstream ifs(f);

        std::stringstream ss;
        ss << ifs.rdbuf();

        files_text.push_back(ss.str());
    }

    std::stringstream ss(files_text[0]);

    rt.start_client(cid, ss);

    auto cmds = rt.get_update_commands(cid);
    
    std::cout << std::ios_base::hex;
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