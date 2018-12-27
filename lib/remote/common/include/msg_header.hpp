#pragma once

#include <cinttypes>

namespace rvi
{
    enum class msg_header : uint8_t
    {
        REQUEST_SNAPSHOT = 0x10,

        BEGIN_SEQUENCE = 0x20,
        END_SEQUENCE = 0x21,

        SELECT_FRAME = 0x30,
        RELEASE_FRAME = 0x31,
        DELETE_FRAME = 0x32,

        DRAW_LINE = 0x40,
        DRAW_LINES = 0x41,

        USER_CLICK = 0xA0,
        USER_KEY = 0xB0,

        DISCONNECT = 0xDC,
        UNKNOWN_ERROR = 0xEE
    };
}