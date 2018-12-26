#pragma once

#include <vector>
#include <cinttypes>
#include <string>

#include <line.hpp>
#include <transform2.hpp>
#include <vector2.hpp>

namespace rvi
{
    typedef std::vector<uint8_t> message_data_t;

    namespace msg_builder
    {
        message_data_t msg_ack();
        message_data_t msg_awating_ack();

        message_data_t msg_begin_seq();
        message_data_t msg_end_seq();

        message_data_t msg_select_frame(const std::string& fname);
        message_data_t msg_release_frame();
        message_data_t msg_delete_frame(const std::string& fname);

        message_data_t msg_draw_line(const rvi::line& ln);
        message_data_t msg_draw_lines(const std::vector<rvi::line>& lines);

        message_data_t msg_set_transform(const rvi::transform2& tform);
        message_data_t msg_set_position(const rvi::vector2& pos);
        message_data_t msg_set_scale(const rvi::vector2& scl);
        message_data_t msg_set_rotation(float rot);

        message_data_t msg_set_color(rvi::color_rgba color);

        message_data_t msg_user_click(rvi::vector2 clk_pos);
        message_data_t msg_user_key(char key);

        message_data_t msg_disconnect();
        message_data_t msg_error();
    }
}