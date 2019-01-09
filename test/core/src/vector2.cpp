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
        float expected = std::sqrt(std::powf(vx, 2) + std::powf(vy, 2));
        REQUIRE(vec.magnitude() == expected);
    }
}

void test_vector2_rotation(double angle_deg)
{
    vector2 vec(rand_float(), rand_float());
    vector2 rotated_vec = vec.rotate(angle_deg);

    double proportion_sin = std::sin(angle_deg);
    double proportion_cos = std::cos(angle_deg);

    double expected_x = vec.magnitude() * proportion_cos;
    double expected_y = vec.magnitude() * proportion_sin;

    REQUIRE((double)rotated_vec.x == expected_x);
    REQUIRE((double)rotated_vec.y == expected_y);
}

TEST_CASE("rvi::vector2::rotate()")
{
    test_vector2_rotation(0);
    test_vector2_rotation(1);
    test_vector2_rotation(5);
    test_vector2_rotation(15);
    test_vector2_rotation(30);
    test_vector2_rotation(45);
    test_vector2_rotation(90);
    test_vector2_rotation(135);
    test_vector2_rotation(180);
    test_vector2_rotation(270);
    test_vector2_rotation(360);
    test_vector2_rotation(-1);
    test_vector2_rotation(-60);
    test_vector2_rotation(-90);
    test_vector2_rotation(-180);
    test_vector2_rotation(-360);
    test_vector2_rotation(2222);
    test_vector2_rotation(-3333);
}