#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <frame.hpp>

#include "random_gen.hpp"

using namespace rvi;

static const int OP_TEST_ITER = 25000;

TEST(Frame, AddLine)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Frame f("test_frame");

        Vertex vx1, vx2;
        const Line ln1(vx1, vx2);

        vx1.Position.OffsetInPlace(Vector2(GetRandomFloat(),GetRandomFloat()));
        vx1.Position.RotateInPlace(GetRandomFloat());
        const Line ln2(vx1, vx2);
        Line ln2_cp = ln2;

        ASSERT_EQ(f.Lines().size(), 0);

        f.AddLine(ln1);
        ASSERT_EQ(f.Lines().size(), 1);
        ASSERT_EQ(f.Lines()[0], ln1);

        f.AddLine(std::move(ln2_cp));
        ASSERT_EQ(f.Lines().size(), 2);
        ASSERT_EQ(f.Lines()[0], ln1);
        ASSERT_EQ(f.Lines()[1], ln2);
    }
}

TEST(Frame, LineCount)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Frame f("test_frame");

        int icount = std::max(10, std::abs(GetRandomInt()));
        for(int i = 0; i < icount; i++)
        {
            Vertex vx1, vx2;
            f.AddLine(Line(vx1,vx2));
        }

        ASSERT_EQ(f.LineCount(), icount);
    }
}

TEST(Frame, ClearLines)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Frame f("test_frame");

        int icount = std::max(10, std::abs(GetRandomInt()));
        for(int i = 0; i < icount; i++)
        {
            Vertex vx1, vx2;
            f.AddLine(Line(vx1,vx2));
        }    
        ASSERT_EQ(f.LineCount(), icount);

        f.ClearLines();
        ASSERT_EQ(f.LineCount(), 0);
    }
}

TEST(Frame, ContainsChildFrame)
{
    Frame parent("test_frame");
    parent.AddChildFrame("child_1");
    parent.AddChildFrame("child_2");
    parent.AddChildFrame("child_3");
    parent.AddChildFrame("child_4");
    
    ASSERT_TRUE(parent.ContainsChildFrame("child_1"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_2"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_3"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_4"));
    ASSERT_FALSE(parent.ContainsChildFrame("child_5"));
}

TEST(Frame, DeleteChildFrame)
{
    Frame parent("test_frame");
    parent.AddChildFrame("child_1");
    parent.AddChildFrame("child_2");
    parent.AddChildFrame("child_3");
    parent.AddChildFrame("child_4");
    
    ASSERT_TRUE(parent.ContainsChildFrame("child_1"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_2"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_3"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_4"));

    parent.DeleteChildFrame("child_2");

    ASSERT_TRUE(parent.ContainsChildFrame("child_1"));
    ASSERT_FALSE(parent.ContainsChildFrame("child_2"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_3"));
    ASSERT_TRUE(parent.ContainsChildFrame("child_4"));

    parent.DeleteChildFrame("child_1");
    parent.DeleteChildFrame("child_3");
    parent.DeleteChildFrame("child_4");

    ASSERT_FALSE(parent.ContainsChildFrame("child_1"));
    ASSERT_FALSE(parent.ContainsChildFrame("child_2"));
    ASSERT_FALSE(parent.ContainsChildFrame("child_3"));
    ASSERT_FALSE(parent.ContainsChildFrame("child_4"));
}

TEST(Frame, GetFlattenedModulatedLines_Simple)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Frame frame("test_frame");
        Vector2 pos(GetRandomFloat(true), GetRandomFloat(true));
        Vector2 scl(GetRandomFloat(true), GetRandomFloat(true));
        float rot = GetRandomFloat();
        Transform2 tform(pos, scl, rot);
        frame.SetTransform(tform);

        Vertex vx1, vx2, vx3, vx4, vx5, vx6;
        vx3.Position.OffsetInPlace(Vector2(GetRandomFloat(true), GetRandomFloat(true)));
        vx4.Position.OffsetInPlace(Vector2(GetRandomFloat(true), GetRandomFloat(true)));
        vx5.Position.OffsetInPlace(Vector2(GetRandomFloat(true), GetRandomFloat(true)));
        vx6.Position.OffsetInPlace(Vector2(GetRandomFloat(true), GetRandomFloat(true)));
        frame.AddLine(Line(vx1, vx2));
        frame.AddLine(Line(vx3, vx4));
        frame.AddLine(Line(vx5, vx6));

        auto lines = frame.GetFlattenedModulatedLines(Transform2::Default());
        ASSERT_EQ(lines.size(), 3);

        Line expected_ln1(vx1, vx2);
        Line expected_ln2(vx3, vx4);
        Line expected_ln3(vx5, vx6);
        expected_ln1.ApplyTransform(Transform2::Default().Merge(tform));
        expected_ln2.ApplyTransform(Transform2::Default().Merge(tform));
        expected_ln3.ApplyTransform(Transform2::Default().Merge(tform));

        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln1) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln2) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln3) != lines.end());
    }
}

TEST(Frame, GetFlattenedModulatedLines_Complex)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        // Parent
        Frame frame("test_frame");
        // First child
        frame.AddChildFrame("child1");
        // Child's child
        frame.GetChildFrame("child1").AddChildFrame("child2");

        Vector2 pos1(1, 1);
        Vector2 scl1(2, 2);
        float rot1 = 0;
        Transform2 tform1(pos1, scl1, rot1);

        Vector2 pos2(2, 2);
        Vector2 scl2(3, 3);
        float rot2 = 90;
        Transform2 tform2(pos2, scl2, rot2);

        Vector2 pos3(3, 3);
        Vector2 scl3(4, 4);
        float rot3 = 180;
        Transform2 tform3(pos3, scl3, rot3);

        frame.SetTransform(tform1);
        frame.GetChildFrame("child1").SetTransform(tform2);
        frame.GetChildFrame("child1").GetChildFrame("child2").SetTransform(tform3);

        Vertex vx1, vx2, vx3, vx4, vx5, vx6;
        vx3.Position.OffsetInPlace(Vector2(1, 1));
        vx4.Position.OffsetInPlace(Vector2(2, 2));
        vx5.Position.OffsetInPlace(Vector2(3, 3));
        vx6.Position.OffsetInPlace(Vector2(4, 4));
        frame.AddLine(Line(vx1, vx2));
        frame.GetChildFrame("child1").AddLine(Line(vx3, vx4));
        frame.GetChildFrame("child1").GetChildFrame("child2").AddLine(Line(vx5, vx6));

        Line expected_1 = Line(vx1, vx2);
        Line expected_2 = Line(vx3, vx4);
        Line expected_3 = Line(vx5, vx6);
        Transform2 expected_tform1 = Transform2::Default().Merge(tform1);
        Transform2 expected_tform2 = Transform2::Default().Merge(tform1).Merge(tform2);
        Transform2 expected_tform3 = Transform2::Default().Merge(tform1).Merge(tform2).Merge(tform3);

        expected_1.ApplyTransform(expected_tform1);
        expected_2.ApplyTransform(expected_tform2);
        expected_3.ApplyTransform(expected_tform3);

        auto lines = frame.GetFlattenedModulatedLines(Transform2::Default());

        ASSERT_EQ(lines.size(), 3);

        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_1) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_2) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_3) != lines.end());
    }
}