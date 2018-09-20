#pragma once

#include "rvi_base.hpp"

#define RVI_CRGBA_STANDARD_COLOR(name, r, g, b, a)\
    static constexpr ColorRGBA name() { return ColorRGBA(0x##r, 0x##g, 0x##b, 0x##a); }

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

        U32 RGBA()
        {
            return (R << 24) | (G << 16) | (B << 8) | (A);
        }

        static ColorRGBA FromRGBA(uint32_t rgba);

        bool operator==(ColorRGBA other) const noexcept;
        bool operator!=(ColorRGBA other) const noexcept;

        RVI_CRGBA_STANDARD_COLOR(TRANSPARENT,   00, 00, 00, FF);
        RVI_CRGBA_STANDARD_COLOR(WHITE,         FF, FF, FF, 00);
        RVI_CRGBA_STANDARD_COLOR(BLACK,         00, 00, 00, 00);
        RVI_CRGBA_STANDARD_COLOR(GREY,          80, 80, 80, 00);
        RVI_CRGBA_STANDARD_COLOR(RED,           FF, 00, 00, 00);
        RVI_CRGBA_STANDARD_COLOR(RED_LIGHT,     FF, 80, 80, 00);
        RVI_CRGBA_STANDARD_COLOR(GREEN,         00, FF, 00, 00);
        RVI_CRGBA_STANDARD_COLOR(GREEN_LIGHT,   80, FF, 80, 00);
        RVI_CRGBA_STANDARD_COLOR(BLUE,          00, 00, FF, 00);
        RVI_CRGBA_STANDARD_COLOR(BLUE_LIGHT,    80, 80, FF, 00);
        RVI_CRGBA_STANDARD_COLOR(YELLOW,        FF, FF, 00, 00);
        RVI_CRGBA_STANDARD_COLOR(YELLOW_LIGHT,  FF, FF, 80, 00);
        RVI_CRGBA_STANDARD_COLOR(FUCHSIA,       FF, 00, FF, 00);
        RVI_CRGBA_STANDARD_COLOR(FUCHSIA_LIGHT, FF, 80, FF, 00);
        RVI_CRGBA_STANDARD_COLOR(BROWN,         A5, 2A, 2A, 00);
        RVI_CRGBA_STANDARD_COLOR(MAGENTA,       E1, 09, 80, 00);
    };
}