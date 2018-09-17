#pragma once

#include "rvi_base.hpp"
#include "transform2.hpp"
#include "vertex.hpp"
#include "vector2.hpp"

#include <utility>

namespace rvi
{
    class Line
    {
    public:
        Vertex Start;
        Vertex End;

        constexpr Line() noexcept { }
        Line(const Vertex& start, const Vertex& end) noexcept;
        Line(Vertex&& start, Vertex&& end) noexcept;

        void ApplyOffset(Vector2 offset);
        void ApplyScale(Vector2 scale);
        void ApplyRotation(float rotation);

        void ApplyTransform(const Transform2& tform);

        bool operator==(Line other) const noexcept;
        bool operator!=(Line other) const noexcept;
    };
}