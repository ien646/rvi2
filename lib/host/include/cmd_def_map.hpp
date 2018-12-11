#pragma once

#include <unordered_map>

#include "cmd_type.hpp"
#include "runtime_cmd.hpp"

namespace rvi
{
    extern const std::unordered_map<cmd_type, runtime_cmd_t> cmd_def_map;
}