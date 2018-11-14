#include "str_utils.hpp"

namespace rvi::str_utils
{        
    str_vec_t split(std::string_view strv, char delim)
    {
        str_vec_t result;
        auto beg_it = strv.begin();
        auto cur_it = strv.begin();

        while (cur_it != strv.end())
        {
            if (*cur_it == delim)
            {
                result.push_back(std::string(beg_it, cur_it));
                beg_it = ++cur_it;
            }
            else
            {
                cur_it++;
            }
        }

        result.push_back(std::string(beg_it, cur_it));
        return result;
    }

    str_pair_t split_once_beg(std::string_view strv, char delim)
    {
        str_pair_t result;

        auto found_it = std::find(strv.begin(), strv.end(), delim);
        if (found_it == strv.end())
        {
            result.first = strv;
        }
        else
        {
            result.first = std::string(strv.begin(), found_it);
            if (++found_it != strv.end())
            {
                result.second = std::string(found_it, strv.end());
            }
        }
        return result;
    }

    str_pair_t split_once_end(std::string_view strv, char delim)
    {
        str_pair_t result;

        // -- Reverse start/end iterators
        auto start_it = strv.rbegin();
        auto end_it = strv.rend();

        auto rfound_it = std::find(start_it, end_it, delim);
        auto found_it = rfound_it.base() - 1;
        if (found_it == strv.begin())
        {
            result.first = strv;
        }
        else
        {
            result.first = std::string(strv.begin(), found_it);
            if (++found_it != strv.end())
            {
                result.second = std::string(found_it, strv.end());
            }
        }
        return result;
    }

    std::string_view substr_from_delim(std::string_view strv, char delim)
    {
        std::string_view result;
        auto found_it = std::find(strv.begin(), strv.end(), delim);
        std::ptrdiff_t offset = (found_it - strv.begin()) + 1;
        return strv.substr(offset);
    }

    std::string_view substr_until_delim(std::string_view strv, char delim)
    {
        std::string_view result;
        auto found_it = std::find(strv.begin(), strv.end(), delim);
        std::ptrdiff_t sslen = found_it - strv.begin();
        return strv.substr(0, sslen);
    }
}