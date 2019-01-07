#pragma once

#include <rvi/vector2.hpp>

namespace rvi
{
    /**
     * @brief 2D rectangle class
     */
    struct rectangle
    {
        /**
         * @brief Rectangle position
         */
        vector2 position = vector2::zero();

        /**
         * @brief Rectangle size
         */
        vector2 size = vector2::zero();
        
        /**
         * @brief Default constructor
         */
        constexpr rectangle() { }

        /**
         * @brief Construct a new rectangle object
         * 
         * @param x Horizontal position
         * @param y Vertical position
         * @param w Horizontal size
         * @param h Vertical size
         */
        rectangle(float x, float y, float w, float h);

        /**
         * @brief Construct a new rectangle object
         * 
         * @param pos Rectangle position
         * @param sz Rectangle size
         */
        rectangle(vector2 pos, vector2 sz);

        /**
         * @brief Left line horizontal position
         */
        float left() const noexcept;

        /**
         * @brief Right line horizontal position
         */
        float right() const noexcept;

        /**
         * @brief Bottom line vertical position
         */
        float bottom() const noexcept;

        /**
         * @brief Top line vertical position
         */
        float top() const noexcept;

        /**
         * @brief Left-top corner position
         */
        vector2 corner_left_top() const noexcept;

        /**
         * @brief Right-top corner position
         */
        vector2 corner_right_top() const noexcept;

        /**
         * @brief Left-bottom corner position
         */
        vector2 corner_left_bottom() const noexcept;

        /**
         * @brief Right-bottom corner position
         */
        vector2 corner_right_bottom() const noexcept;

        bool operator==(const rectangle& other) const noexcept;
        bool operator!=(const rectangle& other) const noexcept;

        /**
         * @brief Check if a 2D point is contained within this
         * rectangle's bounds.
         */
        bool contains(vector2 point) const noexcept;

        /**
         * @brief Check if another rectangle is fully contained
         * within this rectangle's bounds
         */
        bool contains(const rectangle& other) const noexcept;

        /**
         * @brief Check if another rectangle is partially intersecting
         * this rectangle's bounds
         */
        bool intersects(const rectangle& other) const noexcept;
    };
}