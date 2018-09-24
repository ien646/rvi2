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

TEST(ClientContext, SetCurrentOffset)
{
    ClientContext ctx;
    Vector2 offset(GetRandomFloat(), GetRandomFloat());
    ctx.SetCurrentOffset(offset);
    
    ASSERT_EQ(ctx.GetCurrentOffset(), offset);
}

TEST(ClientContext, SetCurrentScale)
{
    ClientContext ctx;
    Vector2 scale(GetRandomFloat(), GetRandomFloat());
    ctx.SetCurrentScale(scale);
    
    ASSERT_EQ(ctx.GetCurrentScale(), scale);
}

TEST(ClientContext, SetCurrentRotation)
{
    ClientContext ctx;
    float rot = GetRandomFloat();
    ctx.SetCurrentRotation(rot);

    ASSERT_EQ(ctx.GetCurrentRotation(), rot);
}

TEST(ClientContext, SetCurrentTransform)
{
    ClientContext ctx;
    Vector2 offset(GetRandomFloat(), GetRandomFloat());
    Vector2 scale(GetRandomFloat(), GetRandomFloat());
    float rot = GetRandomFloat();
    Transform2 tform(offset, scale, rot);
    
    ctx.SetCurrentTransform(tform);

    ASSERT_EQ(ctx.GetCurrentTransform(), tform);
}

TEST(ClientContext, Select_Release_Frame)
{
    ClientContext ctx;

    ASSERT_EQ(ctx.SelectedFrame().Name(), ClientContext::MAIN_FRAMENAME);

    ctx.ReleaseFrame();
    ASSERT_EQ(ctx.SelectedFrame().Name(), ClientContext::MAIN_FRAMENAME);

    ctx.SelectFrame("test_frame_1");
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_1");

    ctx.ReleaseFrame();
    ASSERT_EQ(ctx.SelectedFrame().Name(), ClientContext::MAIN_FRAMENAME);

    ctx.SelectFrame("test_frame_2");
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_2");

    ctx.SelectFrame("test_frame_2_1");
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_2_1");

    ctx.ReleaseFrame();
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_2");

    ctx.SelectFrame("test_frame_2_2");
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_2_2");

    ctx.SelectFrame("test_frame_2_2_1");
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_2_2_1");

    ctx.SelectFrame("test_frame_2_2_1_1");
    ASSERT_EQ(ctx.SelectedFrame().Name(), "test_frame_2_2_1_1");
    
}

TEST(ClientContext, FrameCount)
{
    ClientContext ctx;
    ctx.SelectFrame("test_frame_1");
    ctx.ReleaseFrame();
    ctx.SelectFrame("test_frame_2");
    ctx.SelectFrame("test_frame_2_1");
    ctx.ReleaseFrame();
    ctx.SelectFrame("test_frame_2_2");
    ctx.SelectFrame("test_frame_2_2_1");
    ctx.SelectFrame("test_frame_2_2_1_1");

    ASSERT_EQ(ctx.FrameCount(), 7);
}

TEST(ClientContext, ExistsDefinition)
{
    ClientContext ctx;
    Definition def("test_def");

    ASSERT_FALSE(ctx.ExistsDefinition(def.Name()));

    ctx.AddDefinition(def);
    ASSERT_TRUE(ctx.ExistsDefinition(def.Name()));
}

TEST(ClientContext, AddDefinition)
{
    ClientContext ctx;
    Definition def("test_def");

    ASSERT_FALSE(ctx.ExistsDefinition(def.Name()));

    ctx.AddDefinition(def);
    ASSERT_TRUE(ctx.ExistsDefinition(def.Name()));

    Definition def2("test_def2");
    ctx.AddDefinition(def2);
    ASSERT_TRUE(ctx.ExistsDefinition(def2.Name()));
}

TEST(ClientContext, DeleteDefinition)
{
    ClientContext ctx;
    Definition def("test_def");

    ASSERT_FALSE(ctx.ExistsDefinition(def.Name()));

    ctx.AddDefinition(def);
    ASSERT_TRUE(ctx.ExistsDefinition(def.Name()));

    Definition def2("test_def2");
    ctx.AddDefinition(def2);
    ASSERT_TRUE(ctx.ExistsDefinition(def2.Name()));

    ctx.DeleteDefinition(def.Name());
    ASSERT_FALSE(ctx.ExistsDefinition(def.Name()));
    ASSERT_TRUE(ctx.ExistsDefinition(def2.Name()));

    ctx.DeleteDefinition(def2.Name());
    ASSERT_FALSE(ctx.ExistsDefinition(def.Name()));
    ASSERT_FALSE(ctx.ExistsDefinition(def2.Name()));
}

TEST(ClientContext, ExecDefinition)
{
    ClientContext ctx;
    Definition def("test_def");

    bool execOk = false;
    def.AddInstruction([&execOk](ClientContext& ctx) { execOk = true; });

    ctx.AddDefinition(def);

    ASSERT_FALSE(execOk);
    ctx.ExecDefinition(def.Name());
    ASSERT_TRUE(execOk);
}

TEST(ClientContext, GetCurrentFramePath)
{
    ClientContext ctx;

    ASSERT_EQ(ctx.GetCurrentFramePath(), ClientContext::MAIN_FRAMENAME);
    ctx.SelectFrame("A");
    auto expected = ClientContext::MAIN_FRAMENAME 
        + ClientContext::FRAMEPATH_SEPARATOR 
        + "A";
    ASSERT_EQ(ctx.GetCurrentFramePath(), expected);

    ctx.SelectFrame("B");
    expected = ClientContext::MAIN_FRAMENAME 
        + ClientContext::FRAMEPATH_SEPARATOR 
        + "A"
        + ClientContext::FRAMEPATH_SEPARATOR 
        + "B";
    ASSERT_EQ(ctx.GetCurrentFramePath(), expected);
}

TEST(ClientContext, FramePathToFrameWithTransform_1Level)
{
    ClientContext ctx;

    Transform2 tform(Vector2(1, 3), Vector2(3, 2), 45.0F);
    ctx.SetCurrentTransform(tform);

    auto rootPath = ctx.GetCurrentFramePath();
    auto rootPair = ctx.FramePathToFrameWithTransform(rootPath);

    ASSERT_EQ(rootPair.first, tform);
    ASSERT_EQ(rootPair.second.Name(), ClientContext::MAIN_FRAMENAME);
}

TEST(ClientContext, FramePathToFrameWithTransform_2Levels)
{
    ClientContext ctx;

    Transform2 tform(
        Vector2(GetRandomFloat(), GetRandomFloat()), 
        Vector2(GetRandomFloat(), GetRandomFloat()), 
        GetRandomFloat());

    Transform2 ch_tform(
        Vector2(GetRandomFloat(), GetRandomFloat()), 
        Vector2(GetRandomFloat(), GetRandomFloat()), 
        GetRandomFloat());
    ctx.SetCurrentTransform(tform);

    ctx.SelectFrame("childframe");
    ctx.SetCurrentTransform(ch_tform);

    auto childPath = ctx.GetCurrentFramePath();
    auto childPair = ctx.FramePathToFrameWithTransform(childPath);

    Transform2 expectedTform(
        (tform.Position + ch_tform.Position),
        (tform.Scale * ch_tform.Scale),
        Math::ClampAngleDeg(tform.Rotation + ch_tform.Rotation));

    ASSERT_EQ(childPair.first, expectedTform);
    ASSERT_EQ(childPair.second.Name(), "childframe");
}