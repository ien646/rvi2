#include "rvi_math.hpp"

#include <cmath>

namespace rvi
{
    math::Matrix2x2 math::get_2d_rot_matrix(float angle) noexcept
    {
        const float angleRadians = deg2rad(angle);
        return Matrix2x2
        {
            std::cos(angleRadians), -std::sin(angleRadians),
            std::sin(angleRadians),  std::cos(angleRadians)
        };
    }

    float math::clamp_angle_deg(float angle) noexcept
    {
        return std::fabs(std::fmod(angle, 360.0F));
    }

    bool math::fpcmp(float a, float b, int dec_precision)
    {
        const float xa = a * (10 * dec_precision);
        const float xb = b * (10 * dec_precision);

        return std::round(xa) == std::round(xb);
    }
}