#pragma once

#include "rvi_base.hpp"

namespace rvi
{
    class Transform2;

    class Vector2
    {
    public:
        float X = 0.0F;
        float Y = 0.0F;

        constexpr Vector2() noexcept { }

        constexpr Vector2(float x, float y) noexcept 
            : X(x)
            , Y(y)
        {  }

        [[nodiscard]]
        float Magnitude() const noexcept;

        [[nodiscard]]
        Vector2 CrossProduct(Vector2 other) const noexcept;
        void CrossProductInPlace(Vector2 other) noexcept;

        [[nodiscard]]
        Vector2 Offset(Vector2 offset) const noexcept;
        void OffsetInPlace(Vector2 offset) noexcept;

        [[nodiscard]]
        Vector2 Rotate(float angle) const noexcept;
        void RotateInPlace(float angle) noexcept;

        [[nodiscard]]
        Vector2 Reverse() const noexcept;
        void ReverseInPlace() noexcept;

        [[nodiscard]]
        Vector2 Invert() const noexcept;
        void InvertInPlace() noexcept;

        [[nodiscard]]
        Vector2 Scale(float scale) const noexcept;
        [[nodiscard]]
        Vector2 Scale(Vector2 scaleVec) const noexcept;
        void ScaleInPlace(float scale) noexcept;
        void ScaleInPlace(Vector2 scale) noexcept;

        Vector2 operator+(Vector2 other) const noexcept;
        Vector2 operator-(Vector2 other) const noexcept;
        Vector2 operator*(float other) const noexcept;
        Vector2 operator*(Vector2 other) const noexcept;
        Vector2 operator/(float other) const noexcept;
        Vector2 operator/(Vector2 other) const noexcept;

        void operator+=(Vector2 other) noexcept;
        void operator-=(Vector2 other) noexcept;
        void operator*=(float other) noexcept;
        void operator*=(Vector2 other) noexcept;
        void operator/=(float other) noexcept;

        bool operator==(Vector2 other) const noexcept;
        bool operator!=(Vector2 other) const noexcept;
    };
}