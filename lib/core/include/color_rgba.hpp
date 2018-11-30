#pragma once

#include <string>

#include "rvi_base.hpp"

namespace rvi
{
    ///RGBA color data structure
    struct color_rgba : public string_representable
    {
        ///Red channel value
        u8 r = 0;

        ///Green channel value
        u8 g = 0;

        ///Blue channel value
        u8 b = 0;

        ///Alpha channel value
        u8 a = 0;

        ///Construct a new color_rgba object [rgba = (0,0,0,0)]
        constexpr color_rgba() noexcept { };

        /**
         * Construct a new color_rgba object
         * 
         * @param r Red channel value
         * @param g Green channel value
         * @param b Blue channel value
         * @param a Alpha channel value
         */
        constexpr color_rgba(u8 r, u8 g, u8 b, u8 a) noexcept
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        ///Pack channel data into a 4-byte scalar
        u32 rgba()
        {
            return (r << 24) | (g << 16) | (b << 8) | (a);
        }

        /**
         * Construct a new color_rgba from a 4-byte scalar,
         * where each byte represents a channel value
         * 
         * @param rgba 4-byte scalar rgba value
         */
        static color_rgba from_rgba(uint32_t rgba);

        bool operator==(color_rgba other) const noexcept;

        bool operator!=(color_rgba other) const noexcept;

        ///Represent as string
        std::string to_string() const final;
    };
}