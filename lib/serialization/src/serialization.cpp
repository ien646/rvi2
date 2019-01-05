#include "serialization.hpp"

namespace rvi
{
    void serialize_fp32_bf(data_t& buff, float val)
    {
        restrict_ieee_754();
        constexpr size_t sz = sizeof(val);
        uint32_t* valptr = reinterpret_cast<uint32_t*>(&val);
        for(size_t i = 0; i < sz; i++)
        {
            uint8_t bt = SC_U8(*valptr >> ((sz - (i + 1)) * 8));
            buff.push_back(bt);
        }
    }

    void serialize_fp64_bf(data_t& buff, double val)
    {
        restrict_ieee_754();
        constexpr size_t sz = sizeof(val);
        uint64_t* valptr = reinterpret_cast<uint64_t*>(&val);
        for(size_t i = 0; i < sz; i++)
        {
            uint8_t bt = SC_U8(*valptr >> ((sz - (i + 1)) * 8));
            buff.push_back(bt);
        }
    }

    void serialize_line_bf(data_t& buff, const rvi::line& val)
    {
        serialize_vertex_bf(buff, val.start);
        serialize_vertex_bf(buff, val.end);
    }

    void serialize_vertex_bf(data_t& buff, const vertex& val)
    {
        serialize_vector2_bf(buff, val.position);
        serialize_color_rgba_bf(buff, val.color);
    }

    void serialize_vector2_bf(data_t& buff, const vector2& val)
    {
        serialize_fp32_bf(buff, val.x);
        serialize_fp32_bf(buff, val.y);
    }

    void serialize_color_rgba_bf(data_t& buff, const color_rgba& val)
    {
        buff.push_back(val.r);
        buff.push_back(val.g);
        buff.push_back(val.b);
        buff.push_back(val.a);
    }

    void serialize_transform2_bf(data_t& buff, const rvi::transform2& val)
    {
        serialize_vector2_bf(buff, val.position);
        serialize_vector2_bf(buff, val.scale);
        serialize_fp32_bf(buff, val.rotation);
    }

    void serialize_string(data_t& buff, const std::string& val)
    {
        // frame name size
        serialize_integral<uint16_t>(buff, SC_U16(val.size()));

        // frame name
        std::copy(val.begin(), val.end(), std::back_inserter(buff));
    }

    float deserialize_fp32(const data_t& buff, size_t offset)
    {
        restrict_ieee_754();
        constexpr size_t sz = sizeof(float);
        float result;
        uint32_t* result_ptr = reinterpret_cast<uint32_t*>(&result);
        *result_ptr = 0x00000000;
        for(size_t i = 0; i < sz; i++)
        {
            *result_ptr |= (static_cast<uint32_t>(buff[i + offset]) << ((sz - (i + 1)) * 8));
        }
        return result;
    }

    double deserialize_fp64(const data_t& buff, size_t offset)
    {
        restrict_ieee_754();
        constexpr size_t sz = sizeof(double);
        double result;
        uint64_t* result_ptr = reinterpret_cast<uint64_t*>(&result);
        *result_ptr = 0x0000000000000000;
        for(size_t i = 0; i < sz; i++)
        {
            *result_ptr |= (static_cast<uint64_t>(buff[i + offset]) << ((sz - (i + 1)) * 8));
        }
        return result;
    }

    vector2 deserialize_vector2(const data_t& buff, size_t offset)
    {
        float x = deserialize_fp32(buff, offset);
        float y = deserialize_fp32(buff, offset + sizeof(float));
        return vector2(x, y);
    }

    color_rgba deserialize_color_rgba(const data_t& buff, size_t offset)
    {
        uint8_t r = buff[offset + 0];
        uint8_t g = buff[offset + 1];
        uint8_t b = buff[offset + 2];
        uint8_t a = buff[offset + 3];
        return color_rgba(r, g, b, a);
    }

    vertex deserialize_vertex(const data_t& buff, size_t offset)
    {
        vector2 pos = deserialize_vector2(buff, offset);
        color_rgba col = deserialize_color_rgba(buff, offset + sizeof(vector2));
        return vertex(pos, col);
    }

    transform2 deserialize_transform2(const data_t& buff, size_t offset)
    {
        transform2 result = transform2::default_value();
        result.position = deserialize_vector2(buff, offset);
        result.scale = deserialize_vector2(buff, offset + sizeof(vector2));
        result.rotation = deserialize_fp32(buff, offset + (sizeof(vector2) * 2));
        return result;
    }

    line deserialize_line(const data_t& buff, size_t offset)
    {
        line result;
        result.start = deserialize_vertex(buff, offset);
        result.end = deserialize_vertex(buff, offset + sizeof(vertex));
        return result;
    }

    std::string deserialize_string(const data_t& buff, size_t offset)
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
}