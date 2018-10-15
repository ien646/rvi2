#pragma once

#include <string>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace rvi::host
{
    static const std::string DIR_PROGRAM = "data";
    class reader
    {
    public:
        static std::vector<std::string> enum_program_files();
        static std::vector<std::string> get_text_from_files(std::vector<std::string> paths);
    };
}