#pragma once

#include <string>
#include <algorithm>
#include <unordered_map>

#include <rvi/command_type.hpp>

namespace rvi
{
    static const std::unordered_map<std::string, command_type> command_type_map = 
    {
        { "select_frame",   command_type::SELECT_FRAME },
        { "release_frame",  command_type::RELEASE_FRAME },
        { "delete_frame",   command_type::DELETE_FRAME },
        { "draw_line",      command_type::DRAW_LINE },
        { "set_color",      command_type::SET_COLOR },
        { "set_transform",  command_type::SET_TRANSFORM },
        { "set_position",   command_type::SET_POSITION },
        { "set_scale",      command_type::SET_SCALE },
        { "set_rotation",   command_type::SET_ROTATION },
        { "define",         command_type::DEFINE },
        { "undefine",       command_type::UNDEFINE },
        { "macro",          command_type::MACRO },
        { "include",        command_type::INCLUDE },
        { "call",           command_type::CALL },
        { "no_reinclude",   command_type::NO_REINCLUDE },
        { "set_clickable",  command_type::SET_CLICKABLE },
        { "unset_clickable",command_type::UNSET_CLICKABLE }
    };

    extern std::string get_cmd_name(command_type ct);
}