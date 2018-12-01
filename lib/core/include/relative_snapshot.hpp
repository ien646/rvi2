#pragma once

#include <unordered_map>

#include "line.hpp"

namespace rvi
{
    struct relative_snapshot_entry
    {
        std::string name;
        std::vector<line> lines;
        bool deleted;
    };

    struct relative_snapshot
    {
        std::vector<relative_snapshot_entry> entries;
    };
}