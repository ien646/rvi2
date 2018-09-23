#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <client_context.hpp>

#include "random_gen.hpp"

using namespace rvi;

TEST(ClientContext, Ctor_DefaultFrame)
{
    ClientContext ctx;
    auto name = ctx.SelectedFrame().Name();
    ASSERT_EQ(name, ClientContext::MAIN_FRAMENAME);
}

TEST(ClientContext, IsDefaultFrameSelected)
{
    ClientContext ctx;

    ASSERT_TRUE(ctx.IsDefaultFrameSelected());
    ctx.SelectFrame("test_frame");
    ASSERT_FALSE(ctx.IsDefaultFrameSelected());
    ctx.ReleaseFrame();
    ASSERT_TRUE(ctx.IsDefaultFrameSelected());
}

TEST(ClientContext, SelectFrame_CreatesNew)
{
    ClientContext ctx;
    ASSERT_EQ(ctx.FrameCount(), 1);
    auto icount = std::max(10, std::abs(GetRandomInt()));
    for (auto i = 0; i < icount; i++)
    {
        ctx.SelectFrame("test_frame" + i);
    }
    ASSERT_EQ(ctx.FrameCount(), 1 + icount);
}

TEST(ClientContext, SelectFrame_Dupe_NoClearLines)
{
    ClientContext ctx;
    ASSERT_EQ(ctx.FrameCount(), 1);
    ctx.SelectFrame("test_frame");
    auto icount = std::max(10, std::abs(GetRandomInt()));
    for (auto i = 0; i < icount; i++)
    {
        Vertex vx1, vx2;
        ctx.DrawLine(vx1, vx2);
    }
    ctx.ReleaseFrame();
    ctx.SelectFrame("test_frame");
    ASSERT_EQ(icount, ctx.SelectedFrame().LineCount());
}

TEST(ClientContext, DrawLine_MainFrame)
{
    ClientContext ctx;

    auto startCount = ctx.SelectedFrame().LineCount();
    ASSERT_EQ(startCount, 0);

    ctx.DrawLine(Line(Vector2(1, 2), Vector2(3, 4)));
    ctx.DrawLine(Vertex(Vector2(0, 0)), Vertex(Vector2(0, 0)));
    ctx.DrawLine(Vector2(5, 6), ColorRGBA::RED(), Vector2(7, 8), ColorRGBA::BLUE());
    ctx.DrawLine(Vector2(9, 10), Vector2(11, 12));

    auto lcount = ctx.SelectedFrame().LineCount();
    ASSERT_EQ(lcount, 4);

    Line expected_ln1 = Line(Vector2(1, 2), Vector2(3, 4));
    Line expected_ln2 = Line(Vertex(Vector2(0, 0)), Vertex(Vector2(0, 0)));
    Line expected_ln3 = Line(Vertex(Vector2(5, 6), ColorRGBA::RED()), Vertex(Vector2(7, 8), ColorRGBA::BLUE()));
    Line expected_ln4 = Line(Vector2(9, 10), Vector2(11, 12));

    auto lines = ctx.SelectedFrame().Lines();
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln1) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln2) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln3) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln4) != std::end(lines));
}