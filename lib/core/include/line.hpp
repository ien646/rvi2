#pragma once

#include "rvi_base.hpp"
#include "transform2.hpp"
#include "vertex.hpp"
#include "vector2.hpp"

#include <utility>

namespace rvi
{
    struct line
    {
        vertex start;
        vertex end;

        constexpr line() noexcept { }
        line(const vertex& start, const vertex& end) noexcept;
        line(vertex&& start, vertex&& end) noexcept;

        void apply_position(vector2 offset);
        void apply_scale(vector2 scale);
        void apply_rotation(float rotation);

        void apply_transform(const transform2& tform);

        bool operator==(line other) const noexcept;
        bool operator!=(line other) const noexcept;

        std::string to_string() const;
    };
}