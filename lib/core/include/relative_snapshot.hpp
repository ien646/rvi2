#pragma once

#include <unordered_map>

#include "line.hpp"

namespace rvi
{
    /**
     * @brief A relative snapshot's entry data
     */
    struct relative_snapshot_entry
    {
        /**
         * @brief Full frame name
         */
        std::string name;

        /**
         * @brief Frame lines
         */
        std::vector<line> lines;

        /**
         * @brief In differential snapshots, used to signal
         * the deletion of the frame. Unused in full snapshots.
         */
        bool deleted = false;
    };

    /**
     * @brief Contains relative snapshot entries.
     */
    struct relative_snapshot
    {
        /**
         * @brief Snapshot entries
         */
        std::vector<relative_snapshot_entry> entries;
    };
}