#pragma once

#include <unordered_map>

#include <rvi/command_type.hpp>
#include <rvi/runtime_cmd.hpp>

#define RVI_RT_CMD_ENTRY(name) \
    void name( \
        [[maybe_unused]] client_instance& c_inst, \
        [[maybe_unused]] const arglist_t& args)

namespace rvi
{
    extern const std::unordered_map<command_type, runtime_cmd_t> command_definitions;

    namespace command_impl
    {
        RVI_RT_CMD_ENTRY(macro);
        RVI_RT_CMD_ENTRY(define);
        RVI_RT_CMD_ENTRY(delete_frame);
        RVI_RT_CMD_ENTRY(draw_line);
        RVI_RT_CMD_ENTRY(call);
        RVI_RT_CMD_ENTRY(include);
        RVI_RT_CMD_ENTRY(invalid_cmd);
        RVI_RT_CMD_ENTRY(no_reinclude);
        RVI_RT_CMD_ENTRY(release_frame);
        RVI_RT_CMD_ENTRY(select_frame);
        RVI_RT_CMD_ENTRY(set_color);
        RVI_RT_CMD_ENTRY(set_position);
        RVI_RT_CMD_ENTRY(set_rotation);
        RVI_RT_CMD_ENTRY(set_scale);
        RVI_RT_CMD_ENTRY(set_transform);
        RVI_RT_CMD_ENTRY(undefine);
        RVI_RT_CMD_ENTRY(set_clickable);
        RVI_RT_CMD_ENTRY(unset_clickable);
    }
}