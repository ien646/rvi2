/* FILE: color.h */

#pragma once

#include "rvi_base.h"

#define CRGBA_STANDARD_COLOR(name,r,g,b,a)    \
    static constexpr ColorRGBA name() { return ColorRGBA(r, g, b, a); }

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

        constexpr ColorRGBA(U8 r, U8 g, U8 b, U8 a) noexcept
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        CRGBA_STANDARD_COLOR(TRANSPARENT, 0, 0, 0, 255);
        CRGBA_STANDARD_COLOR(WHITE, 255, 255, 255, 0);
        CRGBA_STANDARD_COLOR(BLACK, 0, 0, 0, 0);
        CRGBA_STANDARD_COLOR(GREY, 127, 127, 127, 0);
        CRGBA_STANDARD_COLOR(RED, 255, 0, 0, 0);
        CRGBA_STANDARD_COLOR(RED_LIGHT, 255, 127, 127, 0);
        CRGBA_STANDARD_COLOR(GREEN,0, 255, 0, 0);
        CRGBA_STANDARD_COLOR(GREEN_LIGHT, 127, 255, 127, 0);
        CRGBA_STANDARD_COLOR(BLUE, 0, 0, 255, 0);
        CRGBA_STANDARD_COLOR(BLUE_LIGHT, 127, 127, 255, 0);
        CRGBA_STANDARD_COLOR(YELLOW, 255, 255, 0, 0);
        CRGBA_STANDARD_COLOR(YELLOW_LIGHT, 255, 255, 127, 0);
        CRGBA_STANDARD_COLOR(FUCHSIA, 255, 0, 255, 0);
        CRGBA_STANDARD_COLOR(FUCHSIA_LIGHT, 255, 127, 255, 0);
        CRGBA_STANDARD_COLOR(BROWN, 165, 42, 42, 0);
        CRGBA_STANDARD_COLOR(MAGENTA, 229, 9, 127, 0);

        static constexpr 
    };
}