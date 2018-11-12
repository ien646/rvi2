#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "definition.hpp"
#include "runtime_call.hpp"

namespace rvi::host
{
    struct client_instance_data
    {
        std::unordered_map<std::string, definition> definitions;
        std::unordered_map<std::string, runtime_call_t> bindings;
        std::vector<std::string> include_stack;
        std::vector<std::string> include_once_ids;
    };
};