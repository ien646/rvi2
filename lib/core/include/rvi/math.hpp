#pragma once

#include <rvi/base.hpp>
#include <array>

namespace rvi
{
    namespace math
    {
        /**
         * @brief 2x2 floating point matrix
         */
        typedef std::array<float, 4> Matrix2x2;

        /**
         * @brief PI value floating point constant
         */
        constexpr float PI = 3.141592653589793238F;

        /**
         * @brief Convert an angle represented in degrees to its
         * equivalent angle, represented in radians.
         * 
         * @param angle_deg Angle to convert, in degrees
         * @return constexpr float Converted angle, in radians
         */
        constexpr float deg2rad(float angle_deg)
        {
            return angle_deg * PI / 180;
        }

        /**
         * @brief Convert an angle represented in degrees to its
         * equivalent angle, represented in radians.
         * 
         * @param angle_deg Angle to convert, in degrees
         * @return constexpr float Converted angle, in radians
         */
        constexpr double deg2rad(double angle_deg)
        {
            return angle_deg * PI / 180;
        }

        /**
         * @brief Convert an angle represented in radians to its
         * equivalent angle, represented in degrees.
         * 
         * @param angle_deg Angle to convert, in radians
         * @return constexpr float Converted angle, in degrees
         */
        constexpr float rad2deg(float angle_rad)
        {
            return angle_rad * 180 / PI;
        }

        /**
         * @brief Given a rotation angle, obtain the 2d rotation
         * matrix corresponding to such angle.
         * 
         * @param angle Rotation angle
         * @return Matrix2x2 Resulting 2d rotation matrix
         */
        Matrix2x2 get_2d_rot_matrix(float angle) noexcept;

        /**
         * @brief Clamp an angle to 360degree limits
         * 
         * @param angle Angle to clamp
         * @return float Clamped angle
         */
        float clamp_angle_deg(float angle) noexcept;

        /**
         * @brief Reduced precision floating point comparer
         * 
         * @param a Value 'a'
         * @param b Value 'b'
         * @param dec_precision Establishes the maximum amount of
         * decimal positions to take into account during comparison.
         * @return true Values 'a' and 'b' are equal
         * @return false Values 'a' and 'b' are not equal
         */
        bool fpcmp(float a, float b, int dec_precision = 5);
    }
}