/* FILE: line.h */
#pragma once

#include "rviBase.h"
#include "vertex.h"

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

        void ApplyTransform(const Transform2& tform) noexcept;
    };
}