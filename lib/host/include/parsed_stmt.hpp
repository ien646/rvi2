#pragma once

#include <vector>
#include <string>
#include <cmd_type.hpp>

namespace rvi
{
    struct parsed_stmt
    {
        cmd_type cmd;
        std::vector<std::string> args;
    };
}