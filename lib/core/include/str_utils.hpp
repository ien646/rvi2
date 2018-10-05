#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cinttypes>
#include <cctype>

namespace rvi
{
    extern std::vector<std::string> str_split(const std::string& str, char delim);

    extern std::vector<std::string> str_split_once(const std::string& str, char delim);

    extern std::string str_tolower(const std::string& str);

    extern std::string str_trim(const std::string& str);
}