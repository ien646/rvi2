#pragma once

#include "vector2.hpp"

namespace rvi
{
    struct rectangle
    {
        vector2 position = vector2::zero();
        vector2 size = vector2::zero();

        rectangle() = default;
        rectangle(const rectangle& cp_src) = default;
        rectangle(rectangle&& mv_src) = default;
        
        rectangle(float x, float y, float w, float h);
        rectangle(vector2 pos, vector2 sz);

        bool operator==(const rectangle& other);
        bool operator!=(const rectangle& other);
    };
}