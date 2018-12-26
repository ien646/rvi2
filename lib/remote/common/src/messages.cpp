#include "messages.hpp"

#include <vector>
#include "serializer.hpp"

namespace rvi
{
    std::vector<uint8_t> no_data_msg(message_header h)
    {
        return std::vector<uint8_t>(
            1, 
            static_cast<uint8_t>(h)
        );
    }

    message_data_t msg_ack()
    {
        return no_data_msg(message_header::ACK);
    }

    message_data_t msg_awating_ack()
    {
        return no_data_msg(message_header::AWAITING_ACK);
    }

    message_data_t msg_begin_seq()
    {
        return no_data_msg(message_header::BEGIN_SEQUENCE);
    }

    message_data_t msg_end_seq()
    {
        return no_data_msg(message_header::END_SEQUENCE);
    }

    message_data_t select_frame(const std::string& fname)
    {
        message_data_t result;
        result.push_back(static_cast<uint8_t>(message_header::SELECT_FRAME));
        serialize_string(result, fname);
        return result;
    }

    message_data_t release_frame()
    {
        return no_data_msg(message_header::RELEASE_FRAME);
    }

    message_data_t delete_frame(const std::string& fname)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::DELETE_FRAME));
        serialize_string(result, fname);
        return result;
    }

    message_data_t draw_line(const rvi::line& ln)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::DRAW_LINE));
        serialize_line_bf(result, ln);
        return result;
    }

    message_data_t draw_lines(const std::vector<rvi::line>& lines)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::DRAW_LINES));
        for(auto& ln : lines)
        {
            serialize_line_bf(result, ln);
        }
        return result;
    }

    message_data_t set_transform(const rvi::transform2& tform)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::SET_TRANSFORM));
        serialize_transform2_bf(result, tform);
        return result;
    }

    message_data_t set_position(const rvi::vector2& pos)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::SET_POSITION));
        serialize_vector2_bf(result, pos);
        return result;
    }

    message_data_t set_scale(const rvi::vector2& scl)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::SET_SCALE));
        serialize_vector2_bf(result, scl);
        return result;
    }

    message_data_t set_rotation(float rot)
    {
        message_data_t result;
        result.push_back(SC_U8(message_header::SET_ROTATION));
        serialize_fp32_bf(result, rot);
        return result;
    }
}
