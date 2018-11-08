#pragma once

#include "rvi_base.hpp"

namespace rvi
{
    class transform2;

    struct vector2
    {
        float x = 0.0F;
        float y = 0.0F;

        constexpr vector2() noexcept { }

        constexpr vector2(float x, float y) noexcept 
            : x(x)
            , y(y)
        {  }

        [[nodiscard]]
        float magnitude() const noexcept;

        [[nodiscard]]
        vector2 cross_product(vector2 other) const noexcept;
        void cross_product_in_place(vector2 other) noexcept;

        [[nodiscard]]
        vector2 offset(vector2 offset) const noexcept;
        void offset_in_place(vector2 offset) noexcept;

        [[nodiscard]]
        vector2 rotate(float angle) const noexcept;
        void rotate_in_place(float angle) noexcept;

        [[nodiscard]]
        vector2 reverse() const noexcept;
        void reverse_in_place() noexcept;

        [[nodiscard]]
        vector2 invert() const noexcept;
        void invert_in_place() noexcept;

        [[nodiscard]]
        vector2 scale(float scale) const noexcept;
        [[nodiscard]]
        vector2 scale(vector2 scale_vec) const noexcept;
        void scale_in_place(float scale) noexcept;
        void scale_in_place(vector2 scale) noexcept;

        vector2 operator+(vector2 other) const noexcept;
        vector2 operator-(vector2 other) const noexcept;
        vector2 operator*(float other) const noexcept;
        vector2 operator*(vector2 other) const noexcept;
        vector2 operator/(float other) const noexcept;
        vector2 operator/(vector2 other) const noexcept;

        void operator+=(vector2 other) noexcept;
        void operator-=(vector2 other) noexcept;
        void operator*=(float other) noexcept;
        void operator*=(vector2 other) noexcept;
        void operator/=(float other) noexcept;

        bool operator==(vector2 other) const noexcept;
        bool operator!=(vector2 other) const noexcept;

        static constexpr vector2 zero() { return vector2(0,0); }

        std::string to_string() const;
    };
}