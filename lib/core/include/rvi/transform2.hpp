#pragma once

#include <rvi/vector2.hpp>
#include <rvi/math.hpp>
#include <rvi/line.hpp>

#include <vector>

namespace rvi
{
    /**
     * @brief 2D-Transformation data structure. Contains position, scale
     * and rotation information. 
     */
    struct transform2
    {
        /**
         * Transform position
         */
        vector2 position = vector2(0, 0);

        /**
         * Transform scale
         */
        vector2 scale = vector2(1, 1);

        /**
         * Transform rotation
         */
        float rotation = 0.0F;

        /**
         * @brief Default constructor
         */
        constexpr transform2() noexcept { }

        /**
         * @brief Construct a new transform2 object
         * 
         * @param pos Transform position
         * @param scale Transform scale
         * @param rot Transform rotation
         */
        constexpr transform2(vector2 pos, vector2 scale, float rot) noexcept
            : position(pos)
            , scale(scale)
            , rotation(rot)
        { }

        /**
         * @brief Appropiately merge two transforms into one
         * 
         * @param other Transform to merge with
         * @return transform2 Merged transform
         */
        transform2 merge(const transform2& other) const noexcept;

        /**
         * @brief Appropiately merge with another transform
         * 
         * @param other Transform to merge with
         */
        void merge_in_place(const transform2& other) noexcept;

        /**
         * @brief Default transform value
         */
        static constexpr transform2 default_value() 
        { 
            return transform2(vector2::zero(), vector2(1, 1), 0); 
        }

        bool operator==(const transform2& other) const noexcept;
        bool operator!=(const transform2& other) const noexcept;

        /**
         * @brief Convert object to its textual representation
         */
        std::string to_string() const;
    };
}