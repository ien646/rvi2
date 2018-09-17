#include "rvi_math.hpp"

#include <cmath>

namespace rvi
{
    Math::Matrix2x2 Math::Get2DRotationMatrix(float angle) noexcept
    {
        const float angleRadians = Deg2Rad(angle);
        return Matrix2x2
        {
            std::cos(angleRadians), -std::sin(angleRadians),
            std::sin(angleRadians),  std::cos(angleRadians)
        };
    }

    float Math::ClampAngleDeg(float angle) noexcept
    {
        return std::fabs(std::fmod(angle, 360.0F));
    }
}