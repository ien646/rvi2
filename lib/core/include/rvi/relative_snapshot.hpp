#pragma once

#include <unordered_map>

#include <rvi/line.hpp>

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
     * @brief Contains a snapshot of a client_context's frame's
     * lines, alongside the frame names. 
     */
    typedef std::vector<relative_snapshot_entry> relative_snapshot;
}