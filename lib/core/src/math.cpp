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
        /*************************************************************************************
         * Benchmarking (gcc-8/clang-7 -O3 x86-64) showed that conditionally avoiding 'fmod' 
         * keeps roughly the same performance (<1% difference) as unconditionally applying it 
         * on a random set of angles (std::rand()), while improving performance over 1000% on
         * sets of angles with absolute values lower than 360 degrees on average. 
        *************************************************************************************/

        if(angle >= 0.0F)
        {
            if(angle < 360.0F)
            {
                return angle;
            }
            else
            {
                return std::fmod(angle, 360.0F);
            }
        }
        else
        {
            if(angle >= -360.0F)
            {
                return 360 + angle;
            }
            else
            {
                return 360 + std::fmod(angle, 360.0F);
            }
        }
    }

    bool math::fpcmp(float a, float b, int dec_precision)
    {
        const float xa = a * (10 * dec_precision);
        const float xb = b * (10 * dec_precision);

        return std::round(xa) == std::round(xb);
    }
}