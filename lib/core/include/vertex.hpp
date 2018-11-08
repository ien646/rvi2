#pragma once

#include "rvi_base.hpp"
#include "vector2.hpp"
#include "color_rgba.hpp"

namespace rvi
{
    struct vertex
    {
        vector2 position;
        color_rgba color;

        constexpr vertex() noexcept { }
        vertex(float x, float y) noexcept;
        vertex(float x, float y, u8 r, u8 g, u8 b, u8 a) noexcept;
        vertex(vector2 pos) noexcept;
        vertex(vector2 pos, color_rgba vx_color) noexcept;

        bool operator==(vertex other) const noexcept;
        bool operator!=(vertex other) const noexcept;

        std::string to_string() const;
    };
}