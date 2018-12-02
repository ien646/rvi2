#pragma once

#include <string>
#include <vector>

#include <rectangle.hpp>

namespace rvi
{
    struct clickable_frame_data
    {
        std::string binding_name;
        std::vector<std::string> binding_args;
        float depth_value = 0.0F;
        rectangle rect;
        frame* fptr;
    };
}