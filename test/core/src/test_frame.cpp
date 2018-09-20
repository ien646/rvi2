#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <frame.hpp>

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