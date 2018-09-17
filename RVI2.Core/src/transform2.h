/* FILE: transform2.h */
#pragma once

#include "vector2.h"
#include "rvi_math.h"
#include "line.h"

#include <vector>

namespace rvi
{
    class Transform2
    {
    public:
        Vector2 Position;
        Vector2 Scale;
        float Rotation = 0.0F;

        constexpr Transform2() noexcept { }
        Transform2(Vector2 pos, Vector2 scale, float rot) noexcept;

        void ApplyTo(std::vector<Line>& vecs) const noexcept;

        Transform2 Merge(const Transform2& other) noexcept;
    };
}