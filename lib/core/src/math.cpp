#include <rvi/math.hpp>

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
        float clamped = std::fmod(std::fabs(angle), 360.0F);
        return (std::fmod(angle, 360.0F) >= 0.0F) ? clamped : 360.0F - clamped;
    }

    bool math::fpcmp(float a, float b, int dec_precision)
    {
        const float xa = a * (10 * dec_precision);
        const float xb = b * (10 * dec_precision);

        return std::round(xa) == std::round(xb);
    }
}