#include "rvi_assert.hpp"

namespace rvi
{
    void rvi_assert(bool cond, const std::string& msg)
    {
        if(!cond)        
            throw std::logic_error(msg);        
    }
}