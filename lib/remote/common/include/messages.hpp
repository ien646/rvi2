#pragma once

#include <vector>
#include <cinttypes>
#include <string>

#include <line.hpp>
#include <transform2.hpp>
#include <vector2.hpp>

#include "message_header.hpp"

namespace rvi
{
    typedef std::vector<uint8_t> message_data_t;

    message_data_t msg_ack();
    message_data_t msg_awating_ack();

    message_data_t msg_begin_seq();
    message_data_t msg_end_seq();

    message_data_t select_frame(const std::string& fname);
    message_data_t release_frame();
    message_data_t delete_frame(const std::string& fname);

    message_data_t draw_line(const rvi::line& ln);
    message_data_t draw_lines(const std::vector<rvi::line>& lines);

    message_data_t set_transform(const rvi::transform2& tform);
    message_data_t set_position(const rvi::vector2& pos);
    message_data_t set_scale(const rvi::vector2& scl);
    message_data_t set_rotation(float rot);
}