#pragma once

#include <vector>
#include "runtime_call.hpp"

namespace rvi::host
{
    typedef std::pair<runtime_call_t, const arglist_t&> definition_call_t;
    struct definition
    {
        std::vector<definition_call_t> instructions;
    };
}