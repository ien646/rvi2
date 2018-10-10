#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <client_context.hpp>

#include "random_gen.hpp"
#include "utils.hpp"

using namespace rvi;

static random_gen rnd;

TEST(client_context, ctor_default_frame)
{
    client_context ctx;
    auto name = ctx.selected_frame()->name();
    ASSERT_EQ(name, client_context::MAIN_FRAMENAME);
}

TEST(client_context, is_root_frame_selected)
{
    client_context ctx;

    ASSERT_TRUE(ctx.is_root_frame_selected());
    ctx.select_frame("test_frame");
    ASSERT_FALSE(ctx.is_root_frame_selected());
    ctx.release_frame();
    ASSERT_TRUE(ctx.is_root_frame_selected());
}

TEST(client_context, select_frame)
{
    client_context ctx;
    ASSERT_EQ(ctx.frame_count(), static_cast<size_t>(1));
    auto icount = std::max(10, std::abs(rnd.get_random_int()));
    for (auto i = 0; i < icount; i++)
    {
        ctx.select_frame("test_frame" + i);
    }
    ASSERT_EQ(ctx.frame_count(), static_cast<size_t>(1 + icount));
}

TEST(client_context, select_frame_dupe_noclear)
{
    client_context ctx;
    ASSERT_EQ(ctx.frame_count(), static_cast<size_t>(1));
    ctx.select_frame("test_frame");
    auto icount = std::max(10, std::abs(rnd.get_random_int()));
    for (auto i = 0; i < icount; i++)
    {
        vertex vx1, vx2;
        ctx.draw_line(vx1, vx2);
    }
    ctx.release_frame();
    ctx.select_frame("test_frame");
    ASSERT_EQ(static_cast<size_t>(icount), ctx.selected_frame()->line_count());
}

TEST(client_context, draw_line_main_frame)
{
    client_context ctx;

    auto startCount = ctx.selected_frame()->line_count();
    ASSERT_EQ(startCount, static_cast<size_t>(0));

    ctx.draw_line(line(vector2(1, 2), vector2(3, 4)));
    ctx.draw_line(vertex(vector2(0, 0)), vertex(vector2(0, 0)));
    ctx.draw_line(vector2(5, 6), color_rgba::RED(), vector2(7, 8), color_rgba::BLUE());
    ctx.draw_line(vector2(9, 10), vector2(11, 12));

    auto lcount = ctx.selected_frame()->line_count();
    ASSERT_EQ(lcount, static_cast<size_t>(4));

    line expected_ln1 = line(vector2(1, 2), vector2(3, 4));
    line expected_ln2 = line(vertex(vector2(0, 0)), vertex(vector2(0, 0)));
    line expected_ln3 = line(vertex(vector2(5, 6), color_rgba::RED()), vertex(vector2(7, 8), color_rgba::BLUE()));
    line expected_ln4 = line(vector2(9, 10), vector2(11, 12));

    auto lines = ctx.selected_frame()->lines();
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln1) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln2) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln3) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln4) != std::end(lines));
}

TEST(client_context, draw_line_child_frame)
{
    client_context ctx;

    ctx.select_frame("child_frame");
    ctx.set_transform(transform2(vector2::zero(), vector2(0.5F, 0.5F), 0.0F));

    auto startCount = ctx.selected_frame()->line_count();
    ASSERT_EQ(startCount, static_cast<size_t>(0));

    ctx.draw_line(line(vector2(1, 2), vector2(3, 4)));
    ctx.draw_line(vertex(vector2(0, 0)), vertex(vector2(0, 0)));
    ctx.draw_line(vector2(5, 6), color_rgba::RED(), vector2(7, 8), color_rgba::BLUE());
    ctx.draw_line(vector2(9, 10), vector2(11, 12));

    auto lcount = ctx.selected_frame()->line_count();
    ASSERT_EQ(lcount, static_cast<size_t>(4));

    line expected_ln1 = line(vector2(1, 2), vector2(3, 4));
    line expected_ln2 = line(vertex(vector2(0, 0)), vertex(vector2(0, 0)));
    line expected_ln3 = line(vertex(vector2(5, 6), color_rgba::RED()), vertex(vector2(7, 8), color_rgba::BLUE()));
    line expected_ln4 = line(vector2(9, 10), vector2(11, 12));

    auto lines = ctx.selected_frame()->lines();
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln1) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln2) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln3) != std::end(lines));
    ASSERT_TRUE(std::find(std::begin(lines), std::end(lines), expected_ln4) != std::end(lines));
}

TEST(client_context, set_position)
{
    client_context ctx;
    vector2 offset(rnd.get_random_float(), rnd.get_random_float());
    ctx.set_position(offset);
    
    ASSERT_EQ(ctx.position(), offset);
}

TEST(client_context, set_scale)
{
    client_context ctx;
    vector2 scale(rnd.get_random_float(), rnd.get_random_float());
    ctx.set_scale(scale);
    
    ASSERT_EQ(ctx.scale(), scale);
}

TEST(client_context, set_rotation)
{
    client_context ctx;
    float rot = rnd.get_random_float();
    ctx.set_rotation(rot);

    ASSERT_EQ(ctx.rotation(), rot);
}

TEST(client_context, set_transform)
{
    client_context ctx;
    vector2 offset(rnd.get_random_float(), rnd.get_random_float());
    vector2 scale(rnd.get_random_float(), rnd.get_random_float());
    float rot = rnd.get_random_float();
    transform2 tform(offset, scale, rot);
    
    ctx.set_transform(tform);

    ASSERT_EQ(ctx.transform(), tform);
}

TEST(client_context, select_release_frame)
{
    client_context ctx;

    ASSERT_EQ(ctx.selected_frame()->name(), client_context::MAIN_FRAMENAME);

    ctx.release_frame();
    ASSERT_EQ(ctx.selected_frame()->name(), client_context::MAIN_FRAMENAME);

    ctx.select_frame("test_frame_1");
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_1");

    ctx.release_frame();
    ASSERT_EQ(ctx.selected_frame()->name(), client_context::MAIN_FRAMENAME);

    ctx.select_frame("test_frame_2");
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_2");

    ctx.select_frame("test_frame_2_1");
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_2_1");

    ctx.release_frame();
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_2");

    ctx.select_frame("test_frame_2_2");
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_2_2");

    ctx.select_frame("test_frame_2_2_1");
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_2_2_1");

    ctx.select_frame("test_frame_2_2_1_1");
    ASSERT_EQ(ctx.selected_frame()->name(), "test_frame_2_2_1_1");
    
}

TEST(client_context, frame_count)
{
    client_context ctx;
    ctx.select_frame("test_frame_1");
    ctx.release_frame();
    ctx.select_frame("test_frame_2");
    ctx.select_frame("test_frame_2_1");
    ctx.release_frame();
    ctx.select_frame("test_frame_2_2");
    ctx.select_frame("test_frame_2_2_1");
    ctx.select_frame("test_frame_2_2_1_1");

    ASSERT_EQ(ctx.frame_count(), static_cast<size_t>(7));
}

TEST(client_context, contains_definition)
{
    client_context ctx;
    definition def("test_def");

    ASSERT_FALSE(ctx.contains_definition(def.name()));

    ctx.add_definition(def);
    ASSERT_TRUE(ctx.contains_definition(def.name()));
}

TEST(client_context, add_definition)
{
    client_context ctx;
    definition def("test_def");

    ASSERT_FALSE(ctx.contains_definition(def.name()));

    ctx.add_definition(def);
    ASSERT_TRUE(ctx.contains_definition(def.name()));

    definition def2("test_def2");
    ctx.add_definition(def2);
    ASSERT_TRUE(ctx.contains_definition(def2.name()));
}

TEST(client_context, delete_definition)
{
    client_context ctx;
    definition def("test_def");

    ASSERT_FALSE(ctx.contains_definition(def.name()));

    ctx.add_definition(def);
    ASSERT_TRUE(ctx.contains_definition(def.name()));

    definition def2("test_def2");
    ctx.add_definition(def2);
    ASSERT_TRUE(ctx.contains_definition(def2.name()));

    ctx.delete_definition(def.name());
    ASSERT_FALSE(ctx.contains_definition(def.name()));
    ASSERT_TRUE(ctx.contains_definition(def2.name()));

    ctx.delete_definition(def2.name());
    ASSERT_FALSE(ctx.contains_definition(def.name()));
    ASSERT_FALSE(ctx.contains_definition(def2.name()));
}

TEST(client_context, execute_definition)
{
    client_context ctx;
    definition def("test_def");

    bool execOk = false;
    def.add_instruction([&execOk](client_context& ctx) 
    { 
        UNREFERENCED_PARAMETER(ctx);
        execOk = true; 
    });

    ctx.add_definition(def);

    ASSERT_FALSE(execOk);
    ctx.execute_definition(def.name());
    ASSERT_TRUE(execOk);
}

TEST(client_context, get_full_frame_name)
{
    client_context ctx;

    ASSERT_EQ(ctx.get_full_frame_name(), client_context::MAIN_FRAMENAME);
    ctx.select_frame("A");
    auto expected = client_context::MAIN_FRAMENAME 
        + client_context::FRAMEPATH_SEPARATOR 
        + "A";
    ASSERT_EQ(ctx.get_full_frame_name(), expected);

    ctx.select_frame("B");
    expected = client_context::MAIN_FRAMENAME 
        + client_context::FRAMEPATH_SEPARATOR 
        + "A"
        + client_context::FRAMEPATH_SEPARATOR 
        + "B";
    ASSERT_EQ(ctx.get_full_frame_name(), expected);
}

TEST(client_context, extract_fpath_with_transform_1lvl)
{
    client_context ctx;

    transform2 tform(vector2(1, 3), vector2(3, 2), 45.0F);
    ctx.set_transform(tform);

    auto rootPath = ctx.get_full_frame_name();
    const auto rootFrame = ctx.find_frame(rootPath);

    ASSERT_EQ(rootFrame->transform(), tform);
    ASSERT_EQ(rootFrame->name(), client_context::MAIN_FRAMENAME);
}

TEST(client_context, extract_fpath_with_transform_2lvl)
{
    client_context ctx;

    transform2 tform(
        vector2(rnd.get_random_float(), rnd.get_random_float()), 
        vector2(rnd.get_random_float(), rnd.get_random_float()), 
        rnd.get_random_float());

    transform2 ch_tform(
        vector2(rnd.get_random_float(), rnd.get_random_float()), 
        vector2(rnd.get_random_float(), rnd.get_random_float()), 
        rnd.get_random_float());
    ctx.set_transform(tform);

    ctx.select_frame("childframe");
    ctx.set_transform(ch_tform);

    auto childPath = ctx.get_full_frame_name();
    const auto childFrame = ctx.find_frame(childPath);

    ASSERT_EQ(childFrame->transform(), ch_tform);
    ASSERT_EQ(childFrame->name(), "childframe");
}

TEST(client_context, snapshot_full_flat)
{
    client_context ctx;
    ctx.set_transform(transform2::default_value());

    line ln(vector2(1,1), vector2(2,2));

    ctx.draw_line(ln);

    transform2 ch_tform = transform2::default_value();
    ch_tform.position = vector2(1, -1);
    ch_tform.scale = vector2(0.5F, 0.5F);
    ch_tform.rotation = 180.0F;

    ctx.select_frame("child_frame");
    ctx.set_transform(ch_tform);
    ctx.draw_line(ln);

    ctx.select_frame("child_child_frame");
    ctx.set_transform(ch_tform);
    ctx.draw_line(ln);

    auto lines = ctx.snapshot_full_flat();

    line expectedln1(vector2(1, 1), vector2(2, 2)); //diffvec = (1, 1)
    line expectedln2(vector2(2, 0), vector2(1.5F, -0.5F)); // diffvec  =(-0.5, -0.5)
    line expectedln3(vector2(3, -1), vector2(3.25F, -0.75F)); //diffvec = (0.25F, 0.25F)

    ASSERT_TRUE(std::find(lines.begin(), lines.end(), expectedln1) != lines.end());
    ASSERT_TRUE(std::find(lines.begin(), lines.end(), expectedln2) != lines.end());
    ASSERT_TRUE(std::find(lines.begin(), lines.end(), expectedln3) != lines.end());
}

TEST(client_context, snapshot_diff_flat)
{
    // -- Initial snapshot -----------------------------------------
    client_context ctx;
    ctx.set_transform(transform2::default_value());

    line ln(vector2(1,1), vector2(2,2));

    ctx.draw_line(ln);

    transform2 ch_tform = transform2::default_value();
    ch_tform.position = vector2(1, -1);
    ch_tform.scale = vector2(0.5F, 0.5F);
    ch_tform.rotation = 180.0F;

    ctx.select_frame("child_frame");
    ctx.set_transform(ch_tform);
    ctx.draw_line(ln);

    ctx.select_frame("child_child_frame");
    ctx.set_transform(ch_tform);
    ctx.draw_line(ln);

    auto lines_init = ctx.snapshot_diff_flat();

    line expectedln1(vector2(1, 1), vector2(2, 2)); //diffvec = (1, 1)
    line expectedln2(vector2(2, 0), vector2(1.5F, -0.5F)); // diffvec  =(-0.5, -0.5)
    line expectedln3(vector2(3, -1), vector2(3.25F, -0.75F)); //diffvec = (0.25F, 0.25F)

    ASSERT_TRUE(std::find(lines_init.begin(), lines_init.end(), expectedln1) != lines_init.end());
    ASSERT_TRUE(std::find(lines_init.begin(), lines_init.end(), expectedln2) != lines_init.end());
    ASSERT_TRUE(std::find(lines_init.begin(), lines_init.end(), expectedln3) != lines_init.end());

    // -- Empty snapshot -----------------------------------------

    auto lines_empty = ctx.snapshot_diff_flat();

    ASSERT_EQ(lines_empty.size(), static_cast<size_t>(0));

    // -- Partial snapshot (resends entire modified frame) -------
    ctx.draw_line(ln);

    auto lines_partial = ctx.snapshot_diff_flat();

    ASSERT_EQ(lines_partial.size(), static_cast<size_t>(2));
    ASSERT_EQ(std::count(lines_partial.begin(), lines_partial.end(), expectedln3), 2);
}

TEST(client_context, snapshot_diff_relative)
{
    // -- Initial snapshot -----------------------------------------
    client_context ctx;
    ctx.set_transform(transform2::default_value());

    line ln(vector2(1,1), vector2(2,2));

    ctx.draw_line(ln);

    transform2 ch_tform = transform2::default_value();
    ch_tform.position = vector2(1, -1);
    ch_tform.scale = vector2(0.5F, 0.5F);
    ch_tform.rotation = 180.0F;

    ctx.select_frame("child_frame");
    ctx.set_transform(ch_tform);
    ctx.draw_line(ln);

    ctx.select_frame("child_child_frame");
    ctx.set_transform(ch_tform);
    ctx.draw_line(ln);

    auto snapshot_init = ctx.snapshot_diff_relative();   

    line expectedln1(vector2(1, 1), vector2(2, 2)); //diffvec = (1, 1)
    line expectedln2(vector2(2, 0), vector2(1.5F, -0.5F)); // diffvec  =(-0.5, -0.5)
    line expectedln3(vector2(3, -1), vector2(3.25F, -0.75F)); //diffvec = (0.25F, 0.25F)

    auto fname1 = client_context::MAIN_FRAMENAME;
    auto fname2 = fname1 + client_context::FRAMEPATH_SEPARATOR + "child_frame";
    auto fname3 = fname2 + client_context::FRAMEPATH_SEPARATOR +"child_child_frame";

    ASSERT_EQ(snapshot_init.size(), static_cast<size_t>(3));
    ASSERT_EQ(snapshot_init.count(fname1), static_cast<size_t>(1));
    ASSERT_EQ(snapshot_init.count(fname2), static_cast<size_t>(1));
    ASSERT_EQ(snapshot_init.count(fname3), static_cast<size_t>(1));

    ASSERT_EQ(snapshot_init.at(fname1).at(0), ln);
    ASSERT_EQ(snapshot_init.at(fname2).at(0), ln);
    ASSERT_EQ(snapshot_init.at(fname3).at(0), ln);

    // -- Empty snapshot -----------------------------------------

    auto snapshot_empty = ctx.snapshot_diff_flat();

    ASSERT_EQ(snapshot_empty.size(), static_cast<size_t>(0));

    // -- Partial snapshot (resends entire modified frame) -------
    ctx.draw_line(ln);

    auto snapshot_partial = ctx.snapshot_diff_flat();

    ASSERT_EQ(snapshot_partial.size(), static_cast<size_t>(2));
    ASSERT_EQ(std::count(snapshot_partial.begin(), snapshot_partial.end(), expectedln3), 2);
}