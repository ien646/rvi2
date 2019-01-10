#include <catch2/catch.hpp>
#include <rvi/math.hpp>
#include <cmath>

using namespace rvi;

TEST_CASE("rvi::math::clamp_angle_deg()")
{
    SECTION("Exactly 0 degrees")
    {
        auto angle = Approx(math::clamp_angle_deg(0.0F)).margin(0.00001F);
        REQUIRE(angle == 0.0F);
    }

    SECTION("Positive values between 0.01 - 359.99")
    {
        for(float i = 0.01F; i < 359.99F; i += 0.21F)
        {
            auto angle = Approx(math::clamp_angle_deg(i)).margin(0.00001F);
            REQUIRE(angle == i);
        }
    }

    SECTION("Exactly 360 degrees")
    {
        auto angle = Approx(math::clamp_angle_deg(360.0F)).margin(0.00001F);
        REQUIRE(angle == 0.0F);
    }

    SECTION("Positive values larger than 360 degrees")
    {
        for(float i = 360.01F; i < 1000.0F; i += 1.23F)
        {
            auto angle = Approx(math::clamp_angle_deg(i)).margin(0.00001F);
            REQUIRE(angle == (std::fmod(i, 360.0F)));
        }
    }

    SECTION("Negative values between -0.01 - -359.99")
    {
        for(float i = -0.01F; i > 359.99F; i -= 0.21F)
        {
            auto angle = Approx(math::clamp_angle_deg(i)).margin(0.00001F);
            REQUIRE(angle == (360.0F + i));
        }
    }

    SECTION("Exactly -360 degrees")
    {
        auto angle = Approx(math::clamp_angle_deg(-360.0F)).margin(0.00001F);
        REQUIRE(angle == 0.0F);
    }

    SECTION("Negative values lower than -360 degrees")
    {
        for(float i = -360.01F; i > -1000.0F; i -= 1.23F)
        {
            auto angle = Approx(math::clamp_angle_deg(i)).margin(0.00001F);
            REQUIRE(angle == (360.0F - std::fmod(std::fabs(i), 360.0F)));
        }
    }
}