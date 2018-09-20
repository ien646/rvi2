#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <frame.hpp>

#include "random_gen.hpp"

using namespace rvi;

TEST(Frame, AddLine)
{
    Frame f("test_frame");

    Vertex vx1, vx2;
    const Line ln1(vx1, vx2);

    vx1.Position.OffsetInPlace(Vector2(1,1));
    vx1.Position.RotateInPlace(35.0F);
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

TEST(Frame, LineCount)
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

TEST(Frame, ClearLines)
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

TEST(Frame, GetModulatedLines_Simple)
{
    Frame frame("test_frame");
    Vector2 pos(GetRandomFloat(true), GetRandomFloat(true));
    Vector2 scl(GetRandomFloat(true), GetRandomFloat(true));
    float rot = GetRandomFloat();
    Transform2 tform(pos, scl, rot);
    frame.SetTransform(tform);

    Vertex vx1, vx2, vx3, vx4, vx5, vx6;
    vx3.Position.OffsetInPlace(Vector2(GetRandomFloat(), GetRandomFloat()));
    vx4.Position.OffsetInPlace(Vector2(GetRandomFloat(), GetRandomFloat()));
    vx5.Position.OffsetInPlace(Vector2(GetRandomFloat(), GetRandomFloat()));
    vx6.Position.OffsetInPlace(Vector2(GetRandomFloat(), GetRandomFloat()));
    frame.AddLine(Line(vx1,vx2));
    frame.AddLine(Line(vx3,vx4));
    frame.AddLine(Line(vx5,vx6));

    auto lines = frame.GetModulatedLines(Transform2::Default());
    ASSERT_EQ(lines.size(), 3);

    Line expected_ln1(vx1, vx2);
    Line expected_ln2(vx3, vx4);
    Line expected_ln3(vx5, vx6);
    expected_ln1.ApplyTransform(tform);
    expected_ln2.ApplyTransform(tform);
    expected_ln3.ApplyTransform(tform);

    ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln1) != lines.end());
    ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln2) != lines.end());
    ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln3) != lines.end());
}