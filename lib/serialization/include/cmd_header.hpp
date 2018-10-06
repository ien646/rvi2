#pragma once

#include <cinttypes>

namespace rvi::serialization
{
    enum class cmd_header : uint8_t
    {
        DRAW_LINE = 0x00,

        SELECT_FRAME = 0x10,
        RELEASE_FRAME = 0x11,
        DELETE_FRAME = 0x12,

        SET_TRANSFORM = 0x20,
    };
}