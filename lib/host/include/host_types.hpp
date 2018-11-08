#pragma once

#include <vector>
#include <string>
#include <functional>

namespace rvi::host
{
    class runtime;

    typedef int cid_t;
    typedef std::vector<std::string> arglist_t;
    typedef std::function<void(cid_t, runtime&, const arglist_t&)> runtime_inst_t;
}