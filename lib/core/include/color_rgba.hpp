#pragma once

#include "rvi_base.hpp"

#define RVI_CRGBA_STANDARD_COLOR(name, r, g, b, a)\
    static constexpr color_rgba name() { return color_rgba(0x##r, 0x##g, 0x##b, 0x##a); }

namespace rvi
{
    class color_rgba
    {
    public:
        u8 r = 0;
        u8 g = 0;
        u8 b = 0;
        u8 a = 0;

        constexpr color_rgba() noexcept { };

        constexpr color_rgba(u8 r, u8 g, u8 b, u8 a) noexcept
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        u32 rgba()
        {
            return (r << 24) | (g << 16) | (b << 8) | (a);
        }

        static color_rgba from_rgba(uint32_t rgba);

        bool operator==(color_rgba other) const noexcept;
        bool operator!=(color_rgba other) const noexcept;

        std::string to_string() const;

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