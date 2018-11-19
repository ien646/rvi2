#pragma once

#include <unordered_map>

#include <cmd_type.hpp>
#include <runtime_call.hpp>

namespace rvi
{
    extern const std::unordered_map<cmd_type, runtime_call_t> call_map;    
}