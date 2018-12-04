#pragma once
#include <string>

namespace rvi
{
    /**
     * @brief Assert a condition. On failure, throws an std::logic_error
     * constructed with the given message
     * 
     * @param cond Assertion condition
     * @param msg Failure message
     */
    extern void rvi_assert(bool cond, const std::string& msg);
}