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
        rectangle rect;
    };
}