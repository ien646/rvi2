#pragma once

#include "rvi_base.hpp"

namespace rvi
{
    struct transform2;

    /**
     * @brief 2D-Vector data structure.
     */
    struct vector2
    {
        /**
         * @brief Horizontal position
         */
        float x = 0.0F;

        /**
         * @brief Vertical position
         */
        float y = 0.0F;

        /**
         * @brief Default constructor
         */
        constexpr vector2() noexcept { }

        /**
         * @brief Construct a new vector2 object
         * 
         * @param x Horizontal position
         * @param y Vertical position
         */
        constexpr vector2(float x, float y) noexcept 
            : x(x)
            , y(y)
        {  }

        /**
         * @brief Obtain the euclidean norm (magnitude) of the vector
         */
        [[nodiscard]]
        float magnitude() const noexcept;

        /**
         * @brief Obtain the cross product of this vector2
         * against another provided vector2
         * 
         * @param other vector2 to perform cross product against
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 cross_product(vector2 other) const noexcept;

        /**
         * @brief Apply the cross product of this vector2
         * against another provided vector2
         * 
         * @param other vector2 to perform cross product against
         */
        void cross_product_in_place(vector2 other) noexcept;

        /**
         * @brief Obtain the result of applying an offset
         * to this vector2.
         * 
         * @param offset Offset value
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 offset(vector2 offset) const noexcept;

        /**
         * @brief Apply an offset to this vector.
         * 
         * @param offset Offset value
         */
        void offset_in_place(vector2 offset) noexcept;

        /**
         * @brief Obtain the result of applying a rotation
         * to this vector2.
         * 
         * @param angle Rotation value
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 rotate(float angle) const noexcept;

        /**
         * @brief Apply a rotation to this vector.
         * 
         * @param angle Rotation value
         */
        void rotate_in_place(float angle) noexcept;

        /**
         * @brief Obtain the result of reversing the 
         * sense of this vector2
         * 
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 reverse() const noexcept;

        /**
         * @brief Reverse the sense of this vector2
         */
        void reverse_in_place() noexcept;

        /**
         * @brief Obtain the result of inverting this
         * vector2, so that for 'vector2(a, b)', the result
         * shall be vector2((1 / a), (1 / b))
         * 
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 invert() const noexcept;

        /**
         * @brief Apply an inverion operation on this
         * vector2, so that for 'vector2(a, b)', the result
         * shall be 'vector2((1 / a), (1 / b))'
         * 
         * @return vector2 Resulting vector2
         */
        void invert_in_place() noexcept;

        /**
         * @brief Obtain the result of applying a
         * scalar scaling operation on this vector2.
         * 
         * @param scale Scale value, scalar
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 scale(float scale) const noexcept;

        /**
         * @brief Obtain the result of applying a
         * vectorial scaling operation (cross-product) 
         * on this vector2.
         * 
         * @param scale Scale value, vectorial
         * @return vector2 Resulting vector2
         */
        [[nodiscard]]
        vector2 scale(vector2 scale_vec) const noexcept;

        /**
         * @brief Apply a scalar scaling operation 
         * on this vector2.
         * 
         * @param scale Scale value, scalar
         */
        void scale_in_place(float scale) noexcept;

        /**
         * @brief Apply a vectorial scaling operation 
         * on this vector2.
         * 
         * @param scale Scale value, vectorial
         */
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

        /**
         * @brief Zero initialized vector2
         */
        static constexpr vector2 zero() { return vector2(0,0); }

        /**
         * @brief Convert this vector2 to its textual representation
         */
        std::string to_string() const;
    };
}