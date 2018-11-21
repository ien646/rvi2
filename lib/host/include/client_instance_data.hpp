#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "runtime_call.hpp"

namespace rvi
{
    struct client_instance_data
    {
        std::unordered_map<std::string, std::string> definitions;
        std::unordered_map<std::string, runtime_call_t> bindings;
        std::vector<std::string> include_stack;
        std::unordered_set<std::string> include_once_ids;
    };
};