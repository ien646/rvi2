#include "color_rgba.hpp"

namespace rvi
{
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