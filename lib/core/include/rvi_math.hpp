#pragma once

#include "rvi_base.hpp"
#include <array>

namespace rvi
{
    namespace math
    {
        typedef std::array<float, 4> Matrix2x2;

        constexpr float PI = 3.141592653589793238F;

        constexpr float deg2rad(float angle_deg)
        {
            return angle_deg * PI / 180;
        }

        constexpr float rad2deg(float angle_rad)
        {
            return angle_rad * 180 / PI;
        }

        Matrix2x2 get_2d_rot_matrix(float angle) noexcept;

        float clamp_angle_deg(float angle) noexcept;

        bool fpcmp(float a, float b, int dec_precision = 5);
    }
}