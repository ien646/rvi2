#include "reader.hpp"

#include <fstream>    

namespace rvi::host
{
    std::vector<std::string> reader::enum_program_files()
    {
        std::vector<std::string> result;
        if(!std::filesystem::exists(DIR_PROGRAM))
        {
            return result;
        }

        fs::recursive_directory_iterator it(DIR_PROGRAM, fs::directory_options::none);
        for(auto& dir_entry : it)
        {
            if(dir_entry.is_regular_file())
            {
                result.push_back(dir_entry.path().string());
            }
        }
        return result;
    }

    std::vector<std::string> reader::get_text_from_files(std::vector<std::string> paths)
    {
        std::vector<std::string> result;
        for(auto& p : paths)
        {
            std::stringstream ss;
            std::ifstream fst;
            fst.open(p);
            ss << fst.rdbuf();
            result.push_back(ss.str());
        }

        return result;
    }
}