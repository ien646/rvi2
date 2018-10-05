#include "str_utils.hpp"

namespace rvi
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

    std::vector<std::string> str_split_once(const std::string& str, char delim)
    {
        std::vector<std::string> result;
        
        bool found = false;
        std::stringstream first("");
        std::stringstream second("");
        for(auto& ch : str)
        {
            if(ch == delim)
            {
                found = true;
                continue;                
            }

            if(found)
                second << ch;
            else
                first << ch;
        }
        result.push_back(first.str());
        result.push_back(second.str());
        return result;
    }

    std::string str_tolower(const std::string& str)
    {
        std::string result = str;
        result.reserve(str.size());

        std::transform(result.begin(), result.end(), result.begin(), [](char c)
        {
            return static_cast<char>(std::tolower(c));
        });
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