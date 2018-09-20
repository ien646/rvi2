#include <gtest/gtest.h>
#include <vertex.hpp>

#include "random_gen.hpp"

using rvi::Vector2;
using rvi::ColorRGBA;
using rvi::Vertex;

static const int OP_TEST_ITER = 250000;

TEST (Vertex, Equality_Operator)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float pos_x = GetRandomFloat();
        float pos_y = GetRandomFloat();
        uint32_t rgba = GetRandomInt();

        Vector2 vpos(pos_x, pos_y);
        ColorRGBA color = ColorRGBA::FromRGBA(rgba);
        
        Vertex vx1(vpos, color);
        Vertex vx2(vpos, color);

        vpos += Vector2(1,1);
        Vertex vx3(vpos, color);

        color.R += 1;
        Vertex vx4(vpos, color);

        ASSERT_TRUE(vx1 == vx2);
        ASSERT_FALSE(vx1 == vx3);
        ASSERT_FALSE(vx1 == vx4);
    }
}

TEST (Vertex, Inequality_Operator)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float pos_x = GetRandomFloat();
        float pos_y = GetRandomFloat();
        uint32_t rgba = GetRandomInt();

        Vector2 vpos(pos_x, pos_y);
        ColorRGBA color = ColorRGBA::FromRGBA(rgba);
        
        Vertex vx1(vpos, color);
        Vertex vx2(vpos, color);

        vpos += Vector2(1,1);
        Vertex vx3(vpos, color);

        color.R += 1;
        Vertex vx4(vpos, color);

        ASSERT_FALSE(vx1 != vx2);
        ASSERT_TRUE(vx1 != vx3);
        ASSERT_TRUE(vx1 != vx4);
    }
}