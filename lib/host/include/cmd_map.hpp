#pragma once

#include <string>
#include <algorithm>
#include <unordered_map>

#include "cmd_type.hpp"

namespace rvi
{
    static const std::unordered_map<std::string, cmd_type> cmd_map = 
    {
        { "select_frame",   cmd_type::SELECT_FRAME },
        { "release_frame",  cmd_type::RELEASE_FRAME },
        { "delete_frame",   cmd_type::DELETE_FRAME },
        { "draw_line",      cmd_type::DRAW_LINE },
        { "set_color",      cmd_type::SET_COLOR },
        { "set_transform",  cmd_type::SET_TRANSFORM },
        { "set_position",   cmd_type::SET_POSITION },
        { "set_scale",      cmd_type::SET_SCALE },
        { "set_rotation",   cmd_type::SET_ROTATION },
        { "define",         cmd_type::DEFINE },
        { "undefine",       cmd_type::UNDEFINE },
        { "macro",          cmd_type::MACRO },
        { "include",        cmd_type::INCLUDE },
        { "call",           cmd_type::CALL },
        { "no_reinclude",   cmd_type::NO_REINCLUDE },
        { "set_clickable",  cmd_type::SET_CLICKABLE },
        { "unset_clickable",cmd_type::UNSET_CLICKABLE }
    };

    extern std::string get_cmd_name(cmd_type ct);
}