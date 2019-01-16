#pragma once

#include <vector>
#include <string>

#include <rvi/command_type.hpp>

namespace rvi
{
    struct parsed_stmt
    {
        command_type cmd = command_type::INVALID_CMD;
        std::vector<std::string> args;
    };
}