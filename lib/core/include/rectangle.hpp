#pragma once

#include "vector2.hpp"

namespace rvi
{
    struct rectangle
    {
        vector2 position = vector2::zero();
        vector2 size = vector2::zero();
        
        constexpr rectangle() { }
        rectangle(float x, float y, float w, float h);
        rectangle(vector2 pos, vector2 sz);

        float left() const noexcept;
        float right() const noexcept;
        float bottom() const noexcept;
        float top() const noexcept;

        vector2 corner_left_top() const noexcept;
        vector2 corner_right_top() const noexcept;
        vector2 corner_left_bottom() const noexcept;
        vector2 corner_right_bottom() const noexcept;

        bool operator==(const rectangle& other) const noexcept;
        bool operator!=(const rectangle& other) const noexcept;

        bool contains(vector2 point) const noexcept;
        bool contains(const rectangle& other) const noexcept;
        bool intersects(const rectangle& other) const noexcept;
    };
}