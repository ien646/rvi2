#pragma once

#include "rvi_base.h"
#include <array>
#include <cmath>

namespace rvi
{
    namespace Math
    {
        typedef std::array<float, 4> Matrix2x2;

        const float PI = 3.141592653589793238F;

        constexpr float Deg2Rad(float angleDeg);

        constexpr float Rad2Deg(float angleRad);

        Matrix2x2 Get2DRotationMatrix(float angle) noexcept;

        float ClampAngleDeg(float angle) noexcept;
    }
}