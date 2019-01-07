#include <rvi/assert.hpp>

#include <stdexcept>

namespace rvi
{
    void assert(bool cond, const std::string& msg)
    {
        if(!cond)        
            throw std::logic_error(msg);
    }
}