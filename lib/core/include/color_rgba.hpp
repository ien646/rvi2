#pragma once

#include <string>

#include "rvi_base.hpp"

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
    };
}