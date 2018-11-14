#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <cinttypes>
#include <cctype>

namespace rvi::str_utils
{
    typedef std::vector<std::string> str_vec_t;
    typedef std::pair<std::string, std::string> str_pair_t;

    [[nodiscard]]
    str_vec_t split(std::string_view strv, char delim);

    [[nodiscard]]
    str_pair_t split_once_beg(std::string_view strv, char delim);

    [[nodiscard]]
    str_pair_t split_once_end(std::string_view strv, char delim);

    [[nodiscard]]
    std::string_view substr_from_delim(std::string_view strv, char delim);

    [[nodiscard]]
    std::string_view substr_until_delim(std::string_view strv, char delim);
}