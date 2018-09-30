#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cinttypes>
#include <cctype>

namespace rvi::host
{
    std::vector<std::string> str_split(const std::string& str, char delim);

    std::string str_tolower(const std::string& str);

    std::string str_trim(const std::string& str);
}