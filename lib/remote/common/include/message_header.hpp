#pragma once

#include <cinttypes>

namespace rvi
{
    enum class message_header : uint8_t
    {
        ACK = 0x00,
        AWAITING_ACK = 0x01,

        SERVER_READY = 0x10,
        CLIENT_READY = 0x11,

        BEGIN_SEQUENCE = 0x20,
        END_SEQUENCE = 0x21,

        SELECT_FRAME = 0x30,
        RELEASE_FRAME = 0x31,
        DELETE_FRAME = 0x32,

        DRAW_LINE = 0x40,
        DRAW_LINES = 0x41,

        SET_TRANSFORM = 0x50,
        SET_POSITION = 0x51,
        SET_SCALE = 0x52,
        SET_ROTATION = 0x53,

        SET_COLOR = 0x60,

        USER_CLICK = 0xA0,
        USER_KEY = 0xB0,

        DISCONNECT = 0xDC,
        ERROR = 0xEE
    };
}