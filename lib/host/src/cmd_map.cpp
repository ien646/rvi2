#include "cmd_map.hpp"

namespace rvi::host
{
    std::string get_cmd_name(cmd_type ct)
    {
        auto it = std::find_if(cmd_map.begin(), cmd_map.end(), [ct](auto&& pair){ return pair.second == ct;});
        if(it != cmd_map.end())
        {
            return it->first;
        }
        else
        {
            return "ERROR: Command typename not found";
        }
    }
}