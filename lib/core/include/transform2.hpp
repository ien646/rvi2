#pragma once

#include "vector2.hpp"
#include "rvi_math.hpp"
#include "line.hpp"

#include <vector>

namespace rvi
{
    class transform2
    {
    public:
        vector2 position;
        vector2 scale;
        float rotation = 0.0F;

        constexpr transform2() noexcept { }
        constexpr transform2(vector2 pos, vector2 scale, float rot) noexcept
            : position(pos)
            , scale(scale)
            , rotation(rot)
        { }

        transform2 merge(const transform2& other) const noexcept;
        void merge_in_place(const transform2& other) noexcept;

        static constexpr transform2 default_value() 
        { 
            return transform2(vector2::zero(), vector2(1, 1), 0); 
        }

        bool operator==(const transform2& other) const noexcept;
        bool operator!=(const transform2& other) const noexcept;

        std::string to_string() const;
    };
}