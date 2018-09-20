#include "color_rgba.hpp"

namespace rvi
{
    ColorRGBA ColorRGBA::FromRGBA(uint32_t rgba)
    {
        ColorRGBA res;

        res.R = static_cast<U8>(rgba >> 24);
        res.G = static_cast<U8>(rgba >> 16);
        res.B = static_cast<U8>(rgba >> 8);
        res.A = static_cast<U8>(rgba);
        
        return res;
    }

    bool ColorRGBA::operator==(ColorRGBA other) const noexcept
    {
        return (R == other.R) 
            && (G == other.G) 
            && (B == other.B) 
            && (A == other.A);
    }

    bool ColorRGBA::operator!=(ColorRGBA other) const noexcept
    {
        return (R != other.R)
            || (G != other.G)
            || (B != other.B)
            || (A != other.A);
    }
}