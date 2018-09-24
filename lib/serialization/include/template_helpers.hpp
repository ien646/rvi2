#pragma once

#include "type_traits"

namespace rvi::serialization
{
    template <typename T>
    using enable_if_integral = std::enable_if_t<std::is_integral_v<T>>;

    template <typename T>
    using enable_if_float = std::enable_if_t<std::is_floating_point_v<T>>;

    template <typename T>
    using enable_if_float_or_integral = std::enable_if_t<
        std::is_integral_v<T> || std::is_floating_point_v<T>>;

    template <typename T>
    using enable_if_std_xstring = std::enable_if_t<
            std::is_same_v<std::basic_string<typename T::value_type>, std::decay_t<T>>>;
}