#include <rvi/command_type_map.hpp>

namespace rvi
{
    std::string get_cmd_name(command_type ct)
    {
        auto it = std::find_if(
            command_type_map.begin(), command_type_map.end(), 
            [ct](auto&& pair)
            { 
                return pair.second == ct;
            }
        );
        if(it != command_type_map.end())
        {
            return it->first;
        }
        else
        {
            throw std::invalid_argument("Invalid command_type!");
        }
    }
}