#include <gtest/gtest.h>

#include "color_rgba.hpp"
#include "random_gen.hpp"

using rvi::color_rgba;
using rvi::u8;

static const int OP_TEST_ITER = 500;
static random_gen rnd;

TEST(color_rgba, equality_op)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        u8 r = static_cast<u8>(rnd.get_random_int());
        u8 g = static_cast<u8>(rnd.get_random_int());
        u8 b = static_cast<u8>(rnd.get_random_int());
        u8 a = static_cast<u8>(rnd.get_random_int());
        color_rgba cl1(r, g, b, a);
        color_rgba cl2(r, g, b, a);
        color_rgba cl3(0, 0, 0, 0);

        ASSERT_TRUE(cl1 == cl2);
        ASSERT_FALSE(cl1 == cl3);
    }
}

TEST(color_rgba, inequality_op)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        u8 r = static_cast<u8>(rnd.get_random_int());
        u8 g = static_cast<u8>(rnd.get_random_int());
        u8 b = static_cast<u8>(rnd.get_random_int());
        u8 a = static_cast<u8>(rnd.get_random_int());
        color_rgba cl1(r, g, b, a);
        color_rgba cl2(r, g, b, a);
        color_rgba cl3(0, 0, 0, 0);

        ASSERT_FALSE(cl1 != cl2);
        ASSERT_TRUE(cl1 != cl3);
    }
}

TEST(color_rgba, rgba_method)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        u8 r = static_cast<u8>(rnd.get_random_int());
        u8 g = static_cast<u8>(rnd.get_random_int());
        u8 b = static_cast<u8>(rnd.get_random_int());
        u8 a = static_cast<u8>(rnd.get_random_int());
        color_rgba color(r, g, b, a);

        uint32_t rgba = color.rgba();
        uint32_t expected_rgba = (r << 24) | (g << 16) | (b << 8) | (a);
        ASSERT_EQ(rgba, expected_rgba);
    }
}

TEST(color_rgba, from_rgba)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        u8 r = static_cast<u8>(rnd.get_random_int());
        u8 g = static_cast<u8>(rnd.get_random_int());
        u8 b = static_cast<u8>(rnd.get_random_int());
        u8 a = static_cast<u8>(rnd.get_random_int());
        uint32_t rgba = (r << 24) | (g << 16) | (b << 8 ) | a;

        color_rgba color = color_rgba::from_rgba(rgba);

        ASSERT_EQ(color.r, r);
        ASSERT_EQ(color.g, g);
        ASSERT_EQ(color.b, b);
        ASSERT_EQ(color.a, a);
    }
}