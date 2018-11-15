#include "str_utils.hpp"

namespace rvi::str_utils
{
    using std::string;
    using std::string_view;

    str_vec_t split(string_view strv, char delim)
    {
        str_vec_t result;
        auto beg_it = strv.begin();
        auto cur_it = strv.begin();

        while (cur_it != strv.end())
        {
            if (*cur_it == delim)
            {
                result.push_back(string(beg_it, cur_it));
                beg_it = ++cur_it;
            }
            else
            {
                cur_it++;
            }
        }

        result.push_back(string(beg_it, cur_it));
        return result;
    }

    str_pair_t split_once_beg(string_view strv, char delim)
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
                result.second = string(found_it, strv.end());
            }
        }
        return result;
    }

    str_pair_t split_once_end(string_view strv, char delim)
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
            result.first = string(strv.begin(), found_it);
            if (++found_it != strv.end())
            {
                result.second = string(found_it, strv.end());
            }
        }
        return result;
    }

    string_view substr_from_delim(string_view strv, char delim)
    {
        std::string_view result;
        auto found_it = std::find(strv.begin(), strv.end(), delim);
        std::ptrdiff_t offset = (found_it - strv.begin()) + 1;
        return strv.substr(offset);
    }

    string_view substr_until_delim(string_view strv, char delim)
    {
        std::string_view result;
        auto found_it = std::find(strv.begin(), strv.end(), delim);
        std::ptrdiff_t sslen = found_it - strv.begin();
        return strv.substr(0, sslen);
    }

    string_view trim_ws_beg(string_view strv)
    {
        int offset = 0;
        auto it = strv.begin();
        while(it != strv.end())
        {
            if(*it == ' ')
            {
                it++;
                offset++;
            }
            else
            {
                return strv.substr(offset);
            }
        }
		return strv;
    }

    string_view trim_ws_end(string_view strv)
    {
        int offset = 0;
        auto it = strv.rbegin();
        while(it != strv.rend())
        {
            if(*it == ' ')
            {
                it++;
                offset++;
            }
            else
            {
                return strv.substr(0, strv.size() - offset);
            }
        }
		return strv;
    }

    string_view trim_ws(string_view strv)
    {
        return trim_ws_beg(trim_ws_end(strv));
    }

    string replace(string_view strv, char old_val, char new_val)
    {
        string result(strv);
        std::replace(result.begin(), result.end(), old_val, new_val);
        return result;
    }

    string replace(string_view strv, string_view old_val, string_view new_val)
    {
        std::string res = string(strv);
        auto cur_it = res.begin();
		
        const auto old_sz = old_val.size();

        for(;;)
        {
            cur_it = std::search(
                cur_it, 
                res.end(),
                old_val.begin(), 
                old_val.end()
            );

            if(cur_it == res.end())
            {
                break;
            }
            else
            {
                res.replace(
                    cur_it, 
                    cur_it + old_sz, 
                    new_val.begin(),
                    new_val.end()
                );
            }
        }

        return res;
    }
}