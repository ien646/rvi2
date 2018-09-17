#pragma once

#include <type_traits>

namespace rvi::serialization
{
    template<typename T>
    constexpr bool IsScalarType()
    {
        return std::is_integral_v<T> || std::is_floating_point_v<T>;
    }
}