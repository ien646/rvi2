#pragma once

#include <rvi/base.hpp>
#include <rvi/transform2.hpp>
#include <rvi/vertex.hpp>
#include <rvi/vector2.hpp>

#include <utility>

namespace rvi
{
    /**
     * @brief Basic line data structure, consisting of two vertices.
     */
    struct line
    {
        ///Start vertex
        vertex start;

        ///End vertex
        vertex end;

        ///Default constructor
        constexpr line() noexcept { }

        ///Construct by copying the vertices
        line(const vertex& start, const vertex& end) noexcept;

        ///Construct by moving the vertices
        line(vertex&& start, vertex&& end) noexcept;

        ///Offset both vertices by the given offset vector
        void apply_position(vector2 offset);

        ///Scale end vertex position relative to the start vertex
        void apply_scale(vector2 scale);

        ///Rotate end vertex around the start vertex
        void apply_rotation(float rotation);

        ///Apply transform to line vertices
        void apply_transform(const transform2& tform);

        bool operator==(line other) const noexcept;
        bool operator!=(line other) const noexcept;

        ///Represent as string
        std::string to_string() const;
    };
}