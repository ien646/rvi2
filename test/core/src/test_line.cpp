#include <gtest/gtest.h>

#include <line.hpp>
#include "random_gen.hpp"

using rvi::line;
using rvi::vector2;
using rvi::color_rgba;
using rvi::vertex;

static const int OP_TEST_ITER = 500;
static random_gen rnd;

static vertex get_rand_vertex(vector2& out_pos, color_rgba out_color)
{
	out_pos = vector2(rnd.get_random_float(), rnd.get_random_float());
	out_color = color_rgba::from_rgba(rnd.get_random_int());
	return vertex(out_pos, out_color);
}

TEST(line, equality_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 pos;
        color_rgba color;
        vertex vx1 = get_rand_vertex(pos, color);
        vertex vx2 = get_rand_vertex(pos, color);

        line l1(vx1, vx2);
        line l2(vx1, vx2);
        vx1.position += vector2(rnd.get_random_float(), rnd.get_random_float());
        line l3(vx1, vx2);
        vx2.position += vector2(rnd.get_random_float(), rnd.get_random_float());
        line l4(vx1, vx2);

        ASSERT_TRUE(l1 == l2);
        ASSERT_FALSE(l2 == l3);
        ASSERT_FALSE(l3 == l4);
    }
}

TEST(line, inequality_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 pos1, pos2;
        color_rgba color1, color2;
        vertex vx1 = get_rand_vertex(pos1, color1);
        vertex vx2 = get_rand_vertex(pos2, color2);

        line l1(vx1, vx2);
        line l2(vx1, vx2);
        vx1.position += vector2(rnd.get_random_float(), rnd.get_random_float());
        line l3(vx1, vx2);
        vx2.position += vector2(rnd.get_random_float(), rnd.get_random_float());
        line l4(vx1, vx2);

        ASSERT_FALSE(l1 != l2);
        ASSERT_TRUE(l2 != l3);
        ASSERT_TRUE(l3 != l4);
    }
}

TEST(line, apply_position)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 pos1, pos2;
        color_rgba color1, color2;
        vertex vx1 = get_rand_vertex(pos1, color1);
        vertex vx2 = get_rand_vertex(pos2, color2);

        line line(vx1, vx2);

        float offset_x = rnd.get_random_float();
        float offset_y = rnd.get_random_float();

        vector2 offset(offset_x, offset_y);

        line.apply_position(offset);

        vertex expect_vx1 = vx1;
        vertex expect_vx2 = vx2;
        expect_vx1.position += offset;
        expect_vx2.position += offset;

        ASSERT_EQ(line.start, expect_vx1);
        ASSERT_EQ(line.end, expect_vx2);
    }
}

TEST(line, apply_rotation)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 pos1, pos2;
        color_rgba color1, color2;
        vertex vx1 = get_rand_vertex(pos1, color1);
        vertex vx2 = get_rand_vertex(pos2, color2);

        line line(vx1, vx2);

        float angle = rnd.get_random_float();;

        line.apply_rotation(angle);

        vertex expect_vx1 = vx1;
        vertex expect_vx2 = vx2;

        // Since Start is the scale/rotation pivot, it is left untouched
        expect_vx2.position -= expect_vx1.position;
        expect_vx2.position.rotate_in_place(angle);
        expect_vx2.position += expect_vx1.position;

        ASSERT_EQ(line.start, expect_vx1);
        ASSERT_EQ(line.end, expect_vx2);
    }
}

TEST(line, apply_scale)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 pos1, pos2;
        color_rgba color1, color2;
        vertex vx1 = get_rand_vertex(pos1, color1);
        vertex vx2 = get_rand_vertex(pos2, color2);

        line line(vx1, vx2);

        const vector2 scale(rnd.get_random_float(), rnd.get_random_float());

        line.apply_scale(scale);

        vertex expect_vx1 = vx1;
        vertex expect_vx2 = vx2;

        // Since Start is the scale/rotation pivot, it is left untouched
        expect_vx2.position -= expect_vx1.position;
        expect_vx2.position.scale_in_place(scale);
        expect_vx2.position += expect_vx1.position;

        ASSERT_EQ(line.start, expect_vx1);
        ASSERT_EQ(line.end, expect_vx2);
    }
}

TEST(line, apply_transform)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 pos1, pos2;
        color_rgba color1, color2;
        const vertex vx1 = get_rand_vertex(pos1, color1);
        const vertex vx2 = get_rand_vertex(pos2, color2);

        line line(vx1, vx2);

        const vector2 pos(rnd.get_random_float(), rnd.get_random_float());
        const vector2 scl(rnd.get_random_float(), rnd.get_random_float());
        const float rot = rnd.get_random_float();
        const rvi::transform2 tform(pos, scl, rot);
        
        line.apply_transform(tform);
        
        vertex expected_vx1 = vx1;
        vertex expected_vx2 = vx2;

		expected_vx1.position.scale_in_place(scl);
		expected_vx2.position.scale_in_place(scl);
		
        expected_vx2.position -= expected_vx1.position;
        expected_vx2.position.rotate_in_place(rot);
        expected_vx2.position += expected_vx1.position;

        expected_vx1.position += pos;
        expected_vx2.position += pos;

        ASSERT_EQ(line.start, expected_vx1);
        ASSERT_EQ(line.end, expected_vx2);
    }
}