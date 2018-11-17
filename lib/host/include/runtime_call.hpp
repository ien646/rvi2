#pragma once

#include <functional>
#include <vector>
#include <string>

namespace rvi
{
    class client_instance;
    typedef std::vector<std::string> arglist_t;
    typedef std::function<void(client_instance&, const arglist_t&)> runtime_call_t;
}