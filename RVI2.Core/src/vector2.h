/* FILE: Vector2.h */
#pragma once

#include "rviBase.h"

namespace rvi
{
    class Transform2;

    class Vector2
    {
    public:
        float X = 0.0F;
        float Y = 0.0F;

        constexpr Vector2() noexcept { }

        Vector2(float x, float y) noexcept;

        float Magnitude() const noexcept;

        Vector2 CrossProduct(Vector2 other) const noexcept;
        void CrossProductInPlace(Vector2 other) noexcept;

        Vector2 Offset(Vector2 offset) const noexcept;
        void OffsetInPlace(Vector2 offset) noexcept;

        Vector2 Rotate(float angle) const noexcept;
        void RotateInPlace(float angle) noexcept;

        Vector2 Reverse() const noexcept;
        void ReverseInPlace() noexcept;

        Vector2 Inverse() const noexcept;
        void InvertInPlace() noexcept;

        Vector2 Scale(float scale) const noexcept;
        Vector2 Scale(Vector2 scaleVec) const noexcept;
        void ScaleInPlace(float scale) noexcept;
        void ScaleInPlace(Vector2 scale) noexcept;

        void ApplyTransform(const Transform2& tform) noexcept;

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
        void operator/=(Vector2 other) noexcept;
    };
}