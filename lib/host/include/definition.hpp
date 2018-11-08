#pragma once

#include <string>
#include <vector>

#include "runtime.hpp"
#include "host_types.hpp"

namespace rvi::host
{    
    struct definition_line
    {
        std::string cmd;
        arglist_t args;
    };

    struct definition
    {
        std::vector<definition_line> lines;
    };
}