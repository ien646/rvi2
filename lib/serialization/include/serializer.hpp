#pragma once

#include <vector>
#include <cinttypes>
#include <string>

#include <line.hpp>

#include "cmd_header.hpp"

namespace rvi::serialization
{
    typedef std::vector<std::uint8_t> data_t;    

    class serializer
    {
    public:
        static data_t select_frame(const std::string& fname);
        static data_t release_frame();
        static data_t delete_frame(const std::string& fname);
        static data_t draw_line(const rvi::line& ln);
        static data_t set_transform(const rvi::transform2& tform);
    };

    static void serialize_fp32_bf(data_t& buff, float val);
    static void serialize_fp64_bf(data_t& buff, double val);
    static void serialize_line_bf(data_t& buff, const rvi::line& val);
    static void serialize_vertex_bf(data_t& buff, const rvi::vertex& val);
    static void serialize_vector2_bf(data_t& buff, const rvi::vector2& val);
    static void serialize_color_rgba_bf(data_t& buff, const rvi::color_rgba& val);
    static void serialize_transform2_bf(data_t& buff, const rvi::transform2& val);
}