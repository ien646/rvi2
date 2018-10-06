#pragma once

namespace rvi::client
{
    enum class client_cmd_type
    {
        SELECT_FRAME,
        RELEASE_FRAME,
        DELETE_FRAME,
        DRAW_LINE,
        SET_TRANSFORM
    };
}