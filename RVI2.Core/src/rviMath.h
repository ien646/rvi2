#pragma once

#include "rviBase.h"
#include <array>
#include <cmath>

namespace rvi
{
    namespace Math
    {
        typedef std::array<float, 4> Matrix2x2;

        const float PI = 3.141592653589793238F;

        extern constexpr float Deg2Rad(float angleDeg);

        extern constexpr float Rad2Deg(float angleRad);

        extern Matrix2x2 Get2DRotationMatrix(float angle) noexcept;
    }
}