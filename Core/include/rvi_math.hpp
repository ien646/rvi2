#pragma once

#include "rvi_base.hpp"
#include <array>

namespace rvi
{
    namespace Math
    {
        typedef std::array<float, 4> Matrix2x2;

        constexpr float PI = 3.141592653589793238F;

        constexpr float Deg2Rad(float angleDeg)
        {
            return angleDeg * PI / 180;
        }

        constexpr float Rad2Deg(float angleRad)
        {
            return angleRad * 180 / PI;
        }

        Matrix2x2 Get2DRotationMatrix(float angle) noexcept;

        float ClampAngleDeg(float angle) noexcept;
    }
}