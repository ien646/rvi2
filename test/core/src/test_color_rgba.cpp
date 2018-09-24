#include <gtest/gtest.h>

#include "color_rgba.hpp"
#include "random_gen.hpp"

using rvi::ColorRGBA;
using rvi::U8;

static const int OP_TEST_ITER = 5000;

TEST(ColorRgba, Equality_Operator)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        U8 r = static_cast<U8>(GetRandomInt());
        U8 g = static_cast<U8>(GetRandomInt());
        U8 b = static_cast<U8>(GetRandomInt());
        U8 a = static_cast<U8>(GetRandomInt());
        ColorRGBA cl1(r, g, b, a);
        ColorRGBA cl2(r, g, b, a);
        ColorRGBA cl3(0, 0, 0, 0);

        ASSERT_TRUE(cl1 == cl2);
        ASSERT_FALSE(cl1 == cl3);
    }
}

TEST(ColorRgba, Inequality_Operator)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        U8 r = static_cast<U8>(GetRandomInt());
        U8 g = static_cast<U8>(GetRandomInt());
        U8 b = static_cast<U8>(GetRandomInt());
        U8 a = static_cast<U8>(GetRandomInt());
        ColorRGBA cl1(r, g, b, a);
        ColorRGBA cl2(r, g, b, a);
        ColorRGBA cl3(0, 0, 0, 0);

        ASSERT_FALSE(cl1 != cl2);
        ASSERT_TRUE(cl1 != cl3);
    }
}

TEST(ColorRgba, RGBA_Method)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        U8 r = static_cast<U8>(GetRandomInt());
        U8 g = static_cast<U8>(GetRandomInt());
        U8 b = static_cast<U8>(GetRandomInt());
        U8 a = static_cast<U8>(GetRandomInt());
        ColorRGBA color(r, g, b, a);

        uint32_t rgba = color.RGBA();

        ASSERT_EQ(rgba, ((r << 24) | (g << 16) | (b << 8) | (a)));
    }
}

TEST(ColorRgba, FromRGBA)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        U8 r = static_cast<U8>(GetRandomInt());
        U8 g = static_cast<U8>(GetRandomInt());
        U8 b = static_cast<U8>(GetRandomInt());
        U8 a = static_cast<U8>(GetRandomInt());
        uint32_t rgba = (r << 24) | (g << 16) | (b << 8 ) | a;

        ColorRGBA color = ColorRGBA::FromRGBA(rgba);

        ASSERT_EQ(color.R, r);
        ASSERT_EQ(color.G, g);
        ASSERT_EQ(color.B, b);
        ASSERT_EQ(color.A, a);
    }
}