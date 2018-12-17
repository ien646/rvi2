#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <deque>

#include "runtime_cmd.hpp"
#include "parsed_stmt.hpp"
#include "clickable_frame_data.hpp"
#include "constrained_buffer.hpp"

namespace rvi
{
    struct client_instance_data
    {
        std::unordered_map<std::string, std::vector<parsed_stmt>> macros;
        std::unordered_map<std::string, runtime_cmd_t> bindings;
        std::vector<std::string> include_stack;
        std::unordered_set<std::string> include_once_ids;
        std::unordered_map<frame*, clickable_frame_data> clickable_frames;
        constrained_buffer<char, 128> key_buffer;
    };
}