#pragma once

#include <client_context.hpp>

#include "client_instance_data.hpp"

namespace rvi::host
{
    struct client_instance
    {
        client_context context;
        client_instance_data data;
    };
}