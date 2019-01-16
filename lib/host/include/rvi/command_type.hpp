#pragma once

namespace rvi
{
    enum class command_type
    {
        INVALID_CMD,

        SELECT_FRAME,
        RELEASE_FRAME,
        DELETE_FRAME,
        DRAW_LINE,
        SET_COLOR,
        SET_TRANSFORM,
        SET_POSITION,
        SET_ROTATION,
        SET_SCALE,
        DEFINE,
        UNDEFINE,
        MACRO,
        INCLUDE,
        NO_REINCLUDE,
        CALL,
        SET_CLICKABLE,
        UNSET_CLICKABLE
    };
}