#include "msg_builder.hpp"

#include <vector>
#include "serialization.hpp"

#include "msg_header.hpp"

namespace rvi
{
    std::vector<uint8_t> no_data_msg(msg_header h)
    {
        return std::vector<uint8_t>(
            1, 
            static_cast<uint8_t>(h)
        );
    }

    message_data_t msg_builder::msg_begin_seq()
    {
        return no_data_msg(msg_header::BEGIN_SEQUENCE);
    }

    message_data_t msg_builder::msg_end_seq()
    {
        return no_data_msg(msg_header::END_SEQUENCE);
    }

    message_data_t msg_builder::msg_select_frame(const std::string& fname)
    {
        message_data_t result;
        result.push_back(static_cast<uint8_t>(msg_header::SELECT_FRAME));
        serialize_string(result, fname);
        return result;
    }

    message_data_t msg_builder::msg_release_frame()
    {
        return no_data_msg(msg_header::RELEASE_FRAME);
    }

    message_data_t msg_builder::msg_delete_frame(const std::string& fname)
    {
        message_data_t result;
        result.push_back(SC_U8(msg_header::DELETE_FRAME));
        serialize_string(result, fname);
        return result;
    }

    message_data_t msg_builder::msg_draw_line(const rvi::line& ln)
    {
        message_data_t result;
        result.push_back(SC_U8(msg_header::DRAW_LINE));
        serialize_line_bf(result, ln);
        return result;
    }

    message_data_t msg_builder::msg_draw_lines(const std::vector<rvi::line>& lines)
    {
        message_data_t result;
        result.push_back(SC_U8(msg_header::DRAW_LINES));
        serialize_integral<uint16_t>(result, lines.size());
        for(auto& ln : lines)
        {
            serialize_line_bf(result, ln);
        }
        return result;
    }

    message_data_t msg_builder::msg_user_click(rvi::vector2 clk_pos)
    {
        message_data_t result;
        result.push_back(SC_U8(msg_header::USER_CLICK));
        serialize_vector2_bf(result, clk_pos);
        return result;
    }

    message_data_t msg_builder::msg_user_key(char key)
    {
        message_data_t result;
        result.push_back(SC_U8(msg_header::USER_KEY));
        serialize_integral<char>(result, key);
        return result;
    }

    message_data_t msg_builder::msg_disconnect()
    {
        return no_data_msg(msg_header::DISCONNECT);
    }

    message_data_t msg_builder::msg_unknown_error()
    {
        return no_data_msg(msg_header::UNKNOWN_ERROR);
    }
}
