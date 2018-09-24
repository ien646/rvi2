#include <gtest/gtest.h>
#include <vertex.hpp>

#include "random_gen.hpp"

using rvi::vector2;
using rvi::color_rgba;
using rvi::vertex;

static const int OP_TEST_ITER = 5000;

TEST (vertex, equality_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float pos_x = get_random_float();
        float pos_y = get_random_float();
        uint32_t rgba = get_random_int();

        vector2 vpos(pos_x, pos_y);
        color_rgba color = color_rgba::from_rgba(rgba);
        
        vertex vx1(vpos, color);
        vertex vx2(vpos, color);

        vpos += vector2(1,1);
        vertex vx3(vpos, color);

        color.r += 1;
        vertex vx4(vpos, color);

        ASSERT_TRUE(vx1 == vx2);
        ASSERT_FALSE(vx1 == vx3);
        ASSERT_FALSE(vx1 == vx4);
    }
}

TEST (vertex, inequality_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float pos_x = get_random_float();
        float pos_y = get_random_float();
        uint32_t rgba = get_random_int();

        vector2 vpos(pos_x, pos_y);
        color_rgba color = color_rgba::from_rgba(rgba);
        
        vertex vx1(vpos, color);
        vertex vx2(vpos, color);

        vpos += vector2(1,1);
        vertex vx3(vpos, color);

        color.r += 1;
        vertex vx4(vpos, color);

        ASSERT_FALSE(vx1 != vx2);
        ASSERT_TRUE(vx1 != vx3);
        ASSERT_TRUE(vx1 != vx4);
    }
}