#pragma once

#include <vector>
#include <cinttypes>
#include <string>

#include <line.hpp>

#include "cmd_header.hpp"
#include "serialization_base.hpp"

namespace rvi::serialization
{
    class serializer
    {
    public:
        static data_t select_frame(const std::string& fname);
        static data_t release_frame();
        static data_t delete_frame(const std::string& fname);
        static data_t draw_line(const rvi::line& ln);
        static data_t set_transform(const rvi::transform2& tform);
    };
}