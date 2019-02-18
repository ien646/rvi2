#include <catch2/catch.hpp>

#include <rvi/vector2.hpp>
#include <rvi/math.hpp>
#include "utils.hpp"

using rvi::vector2;

TEST_CASE("rvi::vector2::magnitude()")
{
    SECTION("Zero Vector")
    {
        vector2 vec;
        REQUIRE(vec.magnitude() == 0.0F);
    }

    SECTION("Horizontal Vector")
    {
        vector2 vec(1.11F, 0.0F);
        REQUIRE(vec.magnitude() == 1.11F);
    }

    SECTION("Vertical Vector")
    {
        vector2 vec(0.0F, 1.11F);
        REQUIRE(vec.magnitude() == 1.11F);
    }

    SECTION("Diagonal vector")
    {
        float vx = 1.22F;
        float vy = 2.11F;
        vector2 vec(vx, vy);
        float expected = std::sqrt(std::pow(vx, 2) + std::pow(vy, 2));
        REQUIRE(vec.magnitude() == expected);
    }
}

void test_vector2_rotation(float angle_deg)
{    
    float clamped_angle_deg = rvi::math::clamp_angle_deg(angle_deg);
    vector2 vec(rand_float(), rand_float());
    vector2 rotated_vec = vec.rotate(clamped_angle_deg);

    float vec_angle = vec.angle();
    float rvec_angle = rotated_vec.angle();

    float expected_angle = rvi::math::clamp_angle_deg(rvec_angle - vec_angle);
    REQUIRE(Approx(expected_angle).margin(0.00001F) == rvi::math::clamp_angle_deg(clamped_angle_deg));
}

TEST_CASE("rvi::vector2::rotate()")
{
    SECTION("Exactly 0 degrees")
    {
        test_vector2_rotation(0);
    }

    SECTION("Positive values between 0.01 - 359.99 degrees")
    {
        for(float i = 0.01F; i < 360.0F; i+= 1.23F)
        {
            test_vector2_rotation(i);
        }
    }

    SECTION("Exactly 360 degrees")
    {
        test_vector2_rotation(360);
    }

    SECTION("Positive values larger than 360 degrees")
    {
        for(float i = 360.01F; i < 3600.0F; i += 11.73F)
        {
            test_vector2_rotation(i);
        }
    }
    
    SECTION("Negative values between -0.01 - -359.99")
    {
        for(float i = -0.01F; i > -360.0F; i -= 1.23F)
        {
            test_vector2_rotation(i);
        }
    }

    SECTION("Exactly -360 degrees")
    {
        test_vector2_rotation(-360.0F);
    }

    SECTION("Values lower than -360 degrees")
    {
        for(float i = -360.01F; i > -3600.0F; i -= 11.73F)
        {
            test_vector2_rotation(i);
        }
    }
}