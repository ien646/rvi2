#pragma once

#include <string>

#include "cmd_header.hpp"
#include "serialization_base.hpp"

namespace rvi
{
    class deserializer
    {
    public:
        static std::string select_frame(const data_t& buff, size_t offset);
        static std::string delete_frame(const data_t& buff, size_t offset);
        static line draw_line(const data_t& buff, size_t offset);
        static transform2 set_transform(const data_t& buff, size_t offset);
    };
}