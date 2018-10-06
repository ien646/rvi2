#include "serializer.hpp"

#include <line.hpp>

namespace rvi::serialization
{
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    static void serialize_integral(data_t& buff, T val)
    {
        constexpr auto tsz = sizeof(T);
        if constexpr (tsz == sizeof(uint8_t))
        {
            buff.push_back(val);
        }
        else
        {
            for (int i = 0; i < tsz; i++)
            {
                uint8_t byt = static_cast<uint8_t>(val >> (i * 8));
                buff.push_back(byt);
            }
        }
    }

    void serialize_fp32_bf(data_t& buff, float val)
    {
        constexpr auto tsz = sizeof(val);

        uint32_t* ptr = reinterpret_cast<uint32_t*>(&val);
        for (int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            buff.push_back(byt);
        }
    }

    void serialize_fp64_bf(data_t& buff, double val)
    {
        constexpr auto tsz = sizeof(val);

        uint64_t* ptr = reinterpret_cast<uint64_t*>(&val);
        for (int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            buff.push_back(byt);
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

    // Static cast to uint8_t
    template<typename T>
    constexpr std::uint8_t SC_U8(T val)
    {
        return static_cast<std::uint8_t>(val);
    }

    // Static cast to uint16_t
    template<typename T>
    constexpr std::uint16_t SC_U16(T val)
    {
        return static_cast<std::uint16_t>(val);
    }

    data_t serializer::select_frame(const std::string& fname)
    {
        data_t result;

        // header
        result.push_back(SC_U8(cmd_header::SELECT_FRAME));

        // frame name size
        serialize_integral<uint16_t>(result, SC_U16(fname.size()));

        // frame name
        std::copy(fname.begin(), fname.end(), std::back_inserter(result));

        return result;
    }

    data_t serializer::release_frame()
    {
        data_t result;

        // header
        result.push_back(SC_U8(cmd_header::RELEASE_FRAME));

        return result;
    }

    data_t serializer::delete_frame(const std::string& fname)
    {
        data_t result;

        // header
        result.push_back(SC_U8(cmd_header::DELETE_FRAME));

        // frame name size
        serialize_integral<uint16_t>(result, SC_U16(fname.size()));

        // frame name
        std::copy(fname.begin(), fname.end(), std::back_inserter(result));

        return result;
    }

    data_t serializer::draw_line(const rvi::line& ln)
    {
        data_t result;

        // header
        result.push_back(SC_U8(cmd_header::DRAW_LINE));

        serialize_line_bf(result, ln);

        return result;
    }

    data_t serializer::set_transform(const rvi::transform2& tform)
    {
        data_t result;

        // header
        result.push_back(SC_U8(cmd_header::SET_TRANSFORM));

        serialize_transform2_bf(result, tform);

        return result;
    }   
}