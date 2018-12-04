#pragma once

#include <vector>
#include <cinttypes>
#include <limits>

#include <line.hpp>
#include "cmd_header.hpp"

namespace rvi
{
    constexpr void restrict_ieee_754()
    {
        static_assert(
            std::numeric_limits<float>::is_iec559,
            "Unable to compile for IEEE-754 non-conforming floating point representation"
        );
    }

    typedef std::vector<std::uint8_t> data_t;

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

    extern cmd_header get_cmd_header(const data_t& buff, size_t offset);

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    void serialize_integral(data_t& buff, T val)
    {
        constexpr size_t sz = sizeof(T);
        for(size_t i = 0; i < sz; i++)
        {
            buff.push_back(SC_U8(val >> (sz - (i + 1)) * 8));
        }
    }

    extern void serialize_fp32_bf(data_t& buff, float val);
    extern void serialize_fp64_bf(data_t& buff, double val);
    extern void serialize_line_bf(data_t& buff, const rvi::line& val);
    extern void serialize_vertex_bf(data_t& buff, const rvi::vertex& val);
    extern void serialize_vector2_bf(data_t& buff, const rvi::vector2& val);
    extern void serialize_color_rgba_bf(data_t& buff, const rvi::color_rgba& val);
    extern void serialize_transform2_bf(data_t& buff, const rvi::transform2& val);

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    T deserialize_integral(const data_t& buff, size_t offset)
    {
        constexpr size_t sz = sizeof(T);
        T result = static_cast<T>(0);
        for(size_t i = 0; i < sz; i++)
        {
            result |= static_cast<uint64_t>(buff[i + offset]) << ((sz - (i + 1)) * 8);
        }
        return result;
    }

    extern float deserialize_fp32(const data_t& buff, size_t offset);

    extern double deserialize_fp64(const data_t& buff, size_t offset);

    extern vector2 deserialize_vector2(const data_t& buff, size_t offset);

    extern color_rgba deserialize_color_rgba(const data_t& buff, size_t offset);

    extern vertex deserialize_vertex(const data_t& buff, size_t offset);

    extern transform2 deserialize_transform2(const data_t& buff, size_t offset);

    extern line deserialize_line(const data_t& buff, size_t offset);
}