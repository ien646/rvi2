/* FILE: color.h */

#pragma once

#include "rviBase.h"

namespace rvi
{
    class ColorRGBA
    {
    public:
        U8 R = 0;
        U8 G = 0;
        U8 B = 0;
        U8 A = 0;

        constexpr ColorRGBA() noexcept { };
        ColorRGBA(U8 r, U8 g, U8 b, U8 a) noexcept;
    };
}