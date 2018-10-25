#pragma once

namespace rvi::host
{
    enum class cmd_type
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
        CALL,
        INCLUDE,
        NO_REINCLUDE,
        EXEC_BIND
    };
}