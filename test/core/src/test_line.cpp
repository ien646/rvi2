#include <gtest/gtest.h>

#include <line.hpp>
#include "random_gen.hpp"

using rvi::Line;
using rvi::Vector2;
using rvi::ColorRGBA;
using rvi::Vertex;

static const int OP_TEST_ITER = 250000;

static Vertex GetRandomVertex(Vector2& out_pos, ColorRGBA out_color)
{
	out_pos = Vector2(GetRandomFloat(), GetRandomFloat());
	out_color = ColorRGBA::FromRGBA(GetRandomInt());
	return Vertex(out_pos, out_color);
}

TEST(Line, EqualityOperator)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 pos;
        ColorRGBA color;
        Vertex vx1 = GetRandomVertex(pos, color);
        Vertex vx2 = GetRandomVertex(pos, color);

        Line l1(vx1, vx2);
        Line l2(vx1, vx2);
        vx1.Position += Vector2(GetRandomFloat(), GetRandomFloat());
        Line l3(vx1, vx2);
        vx2.Position += Vector2(GetRandomFloat(), GetRandomFloat());
        Line l4(vx1, vx2);

        ASSERT_TRUE(l1 == l2);
        ASSERT_FALSE(l2 == l3);
        ASSERT_FALSE(l3 == l4);
    }
}

TEST(Line, InequalityOperator)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 pos1, pos2;
        ColorRGBA color1, color2;
        Vertex vx1 = GetRandomVertex(pos1, color1);
        Vertex vx2 = GetRandomVertex(pos2, color2);

        Line l1(vx1, vx2);
        Line l2(vx1, vx2);
        vx1.Position += Vector2(GetRandomFloat(), GetRandomFloat());
        Line l3(vx1, vx2);
        vx2.Position += Vector2(GetRandomFloat(), GetRandomFloat());
        Line l4(vx1, vx2);

        ASSERT_FALSE(l1 != l2);
        ASSERT_TRUE(l2 != l3);
        ASSERT_TRUE(l3 != l4);
    }
}

TEST(Line, ApplyOffset)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 pos1, pos2;
        ColorRGBA color1, color2;
        Vertex vx1 = GetRandomVertex(pos1, color1);
        Vertex vx2 = GetRandomVertex(pos2, color2);

        Line line(vx1, vx2);

        float offset_x = GetRandomFloat();
        float offset_y = GetRandomFloat();

        Vector2 offset(offset_x, offset_y);

        line.ApplyOffset(offset);

        Vertex expect_vx1 = vx1;
        Vertex expect_vx2 = vx2;
        expect_vx1.Position += offset;
        expect_vx2.Position += offset;

        ASSERT_EQ(line.Start, expect_vx1);
        ASSERT_EQ(line.End, expect_vx2);
    }
}

TEST(Line, ApplyRotation)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 pos1, pos2;
        ColorRGBA color1, color2;
        Vertex vx1 = GetRandomVertex(pos1, color1);
        Vertex vx2 = GetRandomVertex(pos2, color2);

        Line line(vx1, vx2);

        float angle = GetRandomFloat();;

        line.ApplyRotation(angle);

        Vertex expect_vx1 = vx1;
        Vertex expect_vx2 = vx2;

        // Since Start is the scale/rotation pivot, it is left untouched
        expect_vx2.Position -= expect_vx1.Position;
        expect_vx2.Position.RotateInPlace(angle);
        expect_vx2.Position += expect_vx1.Position;

        ASSERT_EQ(line.Start, expect_vx1);
        ASSERT_EQ(line.End, expect_vx2);
    }
}

TEST(Line, ApplyScale)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 pos1, pos2;
        ColorRGBA color1, color2;
        Vertex vx1 = GetRandomVertex(pos1, color1);
        Vertex vx2 = GetRandomVertex(pos2, color2);

        Line line(vx1, vx2);

        const Vector2 scale(GetRandomFloat(), GetRandomFloat());

        line.ApplyScale(scale);

        Vertex expect_vx1 = vx1;
        Vertex expect_vx2 = vx2;

        // Since Start is the scale/rotation pivot, it is left untouched
        expect_vx2.Position.ScaleInPlace(scale);

        ASSERT_EQ(line.Start, expect_vx1);
        ASSERT_EQ(line.End, expect_vx2);
    }
}