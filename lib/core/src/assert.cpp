#include <rvi/assert.hpp>

#include <stdexcept>
#include <iostream>
#include <cassert>

namespace rvi
{
    void rt_assert(bool cond, const std::string& msg)
    {
        if(!cond)
        {
            std::cerr << msg << std::endl;
            throw std::logic_error(msg);
        }
    }

    void debug_assert(bool cond, const std::string& msg)
    {
        #ifndef NDEBUG
            rt_assert(cond, msg);
        #endif
    }
}