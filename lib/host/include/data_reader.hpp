#pragma once

#include <string>
#include <unordered_map>

#include <interpreter.hpp>

namespace rvi::host
{
    struct data_reader_result
    {
        std::vector<std::string> runtime_files;
        std::vector<std::string> init_files;
    };    

    class data_reader
    {   
    public:
        static data_reader_result enum_data_files(std::string_view dir, bool recursive);      
        static std::string get_include_text(const std::string& id);
    };
}