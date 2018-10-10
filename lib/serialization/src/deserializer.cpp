#include "deserializer.hpp"

namespace rvi::serialization
{
    std::string deserializer::select_frame(const data_t& buff, size_t offset)
    {
        std::string result;

        size_t current_offset = offset;
        uint16_t str_len = deserialize_integral<uint16_t>(buff, current_offset);
        current_offset += sizeof(uint16_t);

        result.reserve(str_len);
        std::copy(
            buff.begin() + current_offset, 
            buff.begin() + current_offset + str_len, 
            std::back_inserter(result));

        return result;
    }

    std::string deserializer::delete_frame(const data_t& buff, size_t offset)
    {
        return deserializer::select_frame(buff, offset);
    }

    line deserializer::draw_line(const data_t& buff, size_t offset)
    {
        return deserialize_line(buff, offset);
    }

    transform2 deserializer::set_transform(const data_t& buff, size_t offset)
    {
        return deserialize_transform2(buff, offset);
    }
}