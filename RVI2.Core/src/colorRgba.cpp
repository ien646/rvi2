#include "colorRgba.h"

namespace rvi
{
    constexpr ColorRGBA::ColorRGBA(U8 r, U8 g, U8 b, U8 a) noexcept
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }
}