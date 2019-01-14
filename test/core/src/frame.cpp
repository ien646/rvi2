#include <catch2/catch.hpp>

#include <rvi/frame.hpp>

using rvi::frame;
using rvi::vector2;
using rvi::transform2;

TEST_CASE("rvi::frame::get_absolute_transform()")
{
    frame fp("parent");
    frame* ch1 = fp.add_child("ch1");
    frame* ch2 = ch1->add_child("ch2");
    frame* ch3 = ch2->add_child("ch3");

    fp.set_position(vector2(0.01F, 0.05F));
    ch1->set_position(vector2(-0.05F, -0.5F));
    ch2->set_position(vector2(0.5F, 0.5F));
    ch3->set_position(vector2(0.113F, 0.031F));
    vector2 expected_position((0.01 - 0.05F + 0.5F + 0.113F), (0.05F -0.5F + 0.5F + 0.031F));

    fp.set_scale(vector2(1, 1));
    ch1->set_scale(vector2(0.5F, 0.5F));
    ch2->set_scale(vector2(0.5F, 0.5F));
    ch3->set_scale(vector2(0.5F, 0.5F));
    vector2 expected_scale(0.125F, 0.125F);

    fp.set_rotation(30);
    ch1->set_rotation(90);
    ch2->set_rotation(-130);
    ch3->set_rotation(-50);
    float expected_rotation = 300.0F;

    transform2 abs_tform = ch3->get_absolute_transform();
    REQUIRE(abs_tform.position.x == expected_position.x);
    REQUIRE(abs_tform.position.y == expected_position.y);
    REQUIRE(abs_tform.scale.x == expected_scale.x);
    REQUIRE(abs_tform.scale.y == expected_scale.y);
    REQUIRE(abs_tform.rotation == expected_rotation);
}