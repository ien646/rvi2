#include "str_utils.hpp"

namespace rvi::host
{
    std::vector<std::string> str_split(const std::string& str, char delim)
    {
        std::vector<std::string> result;

        std::string line;
        std::stringstream sstr(str);
        while (std::getline(sstr, line, delim))
        {
            result.push_back(line);
        }
        return result;
    }

    std::string str_tolower(const std::string& str)
    {
        std::string result;
        result.reserve(str.size());

        std::transform(
            str.begin(),
            str.end(),
            result.begin(),
            [](auto c) { return std::tolower(static_cast<int>(c)); });
        return result;
    }

    std::string str_trim(const std::string& str)
    {
        std::string result;
        result.reserve(str.size());

        auto start_it = std::find(str.begin(), str.end(), ' ');
        auto end_it = std::find(str.end(), str.begin(), ' ');

        std::copy(start_it, end_it, std::back_inserter(result));
        return result;
    }
}