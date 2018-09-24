#include "color_rgba.hpp"

namespace rvi
{
    color_rgba color_rgba::from_rgba(uint32_t rgba)
    {
        color_rgba res;

        res.r = static_cast<u8>(rgba >> 24);
        res.g = static_cast<u8>(rgba >> 16);
        res.b = static_cast<u8>(rgba >> 8);
        res.a = static_cast<u8>(rgba);
        
        return res;
    }

    bool color_rgba::operator==(color_rgba other) const noexcept
    {
        return (r == other.r) 
            && (g == other.g) 
            && (b == other.b) 
            && (a == other.a);
    }

    bool color_rgba::operator!=(color_rgba other) const noexcept
    {
        return (r != other.r)
            || (g != other.g)
            || (b != other.b)
            || (a != other.a);
    }
}