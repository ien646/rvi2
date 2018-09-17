#pragma once

#include "type_traits"

namespace rvi::serialization
{
    template <typename T>
    using EnableIfIntegral = std::enable_if_t<std::is_integral_v<T>>;

    template <typename T>
    using EnableIfFloat = std::enable_if_t<std::is_floating_point_v<T>>;

    template <typename T>
    using EnableIfFloatOrIntegral = std::enable_if_t<
        std::is_integral_v<T> || std::is_floating_point_v<T>>;

    template <typename T>
    using EnableIfStdXString = std::enable_if_t<
            std::is_same_v<std::basic_string<typename T::value_type>, std::decay_t<T>>>;
}