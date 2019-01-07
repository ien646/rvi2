#pragma once

#include <rvi/base.hpp>
#include <rvi/vector2.hpp>
#include <rvi/color_rgba.hpp>

namespace rvi
{
    /**
     * @brief 2D-Vertex data structure. 
     * Includes 32-bit color information.
     */
    struct vertex
    {
        /**
         * @brief Vertex position
         */
        vector2 position;

        /**
         * @brief Vertex color
         */
        color_rgba color;

        /**
         * @brief Default constructor
         */
        constexpr vertex() noexcept { }

        /**
         * @brief Construct a new vertex object
         * 
         * @param pos Vertex position
         * @param vx_color Vertex color
         */
        vertex(vector2 pos, color_rgba vx_color) noexcept;

        bool operator==(vertex other) const noexcept;
        bool operator!=(vertex other) const noexcept;

        /**
         * @brief Convert this vertex to its textual representation
         */
        std::string to_string() const;
    };
}