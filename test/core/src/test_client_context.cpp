#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <client_context.hpp>

#include "random_gen.hpp"

using namespace rvi;

TEST(ClientContext, SelectFrame_CreatesNew)
{
    ClientContext ctx;
    ASSERT_EQ(ctx.FrameCount(), 1);
    auto icount = std::max(10, std::abs(GetRandomInt()));
    for(auto i = 0; i < icount; i++)
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