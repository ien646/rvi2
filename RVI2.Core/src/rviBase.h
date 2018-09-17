/* FILE: rviTypes.h */
#pragma once

#include <cstdint>

#define CONCAT(x,y) x##y
#define UNIQUENAME(prefix) CONCAT(prefix,__COUNTER__)

#define DISCARD auto UNIQUENAME(____trash_) =

namespace rvi
{
    typedef std::uint8_t    U8;
    typedef std::uint16_t   U16;
    typedef std::uint32_t   U32;
    typedef std::uint64_t   U64;

    typedef std::int8_t     I8;
    typedef std::int16_t    I16;
    typedef std::int32_t    I32;
    typedef std::int64_t    I64;
}