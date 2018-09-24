#pragma once

#include "vector2.hpp"
#include "rvi_math.hpp"
#include "line.hpp"

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
        constexpr Transform2(Vector2 pos, Vector2 scale, float rot) noexcept
            : Position(pos)
            , Scale(scale)
            , Rotation(rot)
        { }

        Transform2 Merge(const Transform2& other) const noexcept;

        static constexpr Transform2 Default() 
        { 
            return Transform2(Vector2::Zero(), Vector2(1,1), 0); 
        }

        bool operator==(const Transform2& other) const noexcept;
        bool operator!=(const Transform2& other) const noexcept;
    };
}