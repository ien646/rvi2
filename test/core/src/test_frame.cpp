#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <frame.hpp>

#include "random_gen.hpp"

using namespace rvi;

static const int OP_TEST_ITER = 5000;
static random_gen rnd;

TEST(frame, AddLine)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        frame f("test_frame");

        vertex vx1, vx2;
        const line ln1(vx1, vx2);

        vx1.position.offset_in_place(vector2(rnd.get_random_float(),rnd.get_random_float()));
        vx1.position.rotate_in_place(rnd.get_random_float());
        const line ln2(vx1, vx2);
        line ln2_cp = ln2;

        ASSERT_EQ(f.lines().size(), static_cast<size_t>(0));

        f.add_line(ln1);
        ASSERT_EQ(f.lines().size(), static_cast<size_t>(1));
        ASSERT_EQ(f.lines()[0], ln1);

        f.add_line(std::move(ln2_cp));
        ASSERT_EQ(f.lines().size(), static_cast<size_t>(2));
        ASSERT_EQ(f.lines()[0], ln1);
        ASSERT_EQ(f.lines()[1], ln2);
    }
}

TEST(frame, line_count)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        frame f("test_frame");

        int icount = std::max(10, std::abs(rnd.get_random_int()));
        for(int j = 0; j < icount; j++)
        {
            vertex vx1, vx2;
            f.add_line(line(vx1,vx2));
        }

        ASSERT_EQ(f.line_count(), static_cast<size_t>(icount));
    }
}

TEST(frame, clear_lines)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        frame f("test_frame");

        int icount = std::max(10, std::abs(rnd.get_random_int()));
        for(int j = 0; j < icount; j++)
        {
            vertex vx1, vx2;
            f.add_line(line(vx1,vx2));
        }    
        ASSERT_EQ(f.line_count(), static_cast<size_t>(icount));

        f.clear_lines();
        ASSERT_EQ(f.line_count(), static_cast<size_t>(0));
    }
}

TEST(frame, contains_child)
{
    frame parent("test_frame");
    parent.add_child("child_1");
    parent.add_child("child_2");
    parent.add_child("child_3");
    parent.add_child("child_4");
    
    ASSERT_TRUE(parent.contains_child("child_1"));
    ASSERT_TRUE(parent.contains_child("child_2"));
    ASSERT_TRUE(parent.contains_child("child_3"));
    ASSERT_TRUE(parent.contains_child("child_4"));
    ASSERT_FALSE(parent.contains_child("child_5"));
}

TEST(frame, delete_child)
{
    frame parent("test_frame");
    parent.add_child("child_1");
    parent.add_child("child_2");
    parent.add_child("child_3");
    parent.add_child("child_4");
    
    ASSERT_TRUE(parent.contains_child("child_1"));
    ASSERT_TRUE(parent.contains_child("child_2"));
    ASSERT_TRUE(parent.contains_child("child_3"));
    ASSERT_TRUE(parent.contains_child("child_4"));

    parent.delete_child("child_2");

    ASSERT_TRUE(parent.contains_child("child_1"));
    ASSERT_FALSE(parent.contains_child("child_2"));
    ASSERT_TRUE(parent.contains_child("child_3"));
    ASSERT_TRUE(parent.contains_child("child_4"));

    parent.delete_child("child_1");
    parent.delete_child("child_3");
    parent.delete_child("child_4");

    ASSERT_FALSE(parent.contains_child("child_1"));
    ASSERT_FALSE(parent.contains_child("child_2"));
    ASSERT_FALSE(parent.contains_child("child_3"));
    ASSERT_FALSE(parent.contains_child("child_4"));
}

TEST(frame, get_all_modulated_lines_simple)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        frame frame("test_frame");
        vector2 pos(rnd.get_random_float(true), rnd.get_random_float(true));
        vector2 scl(rnd.get_random_float(true), rnd.get_random_float(true));
        float rot = rnd.get_random_float();
        transform2 tform(pos, scl, rot);
        frame.set_transform(tform);

        vertex vx1, vx2, vx3, vx4, vx5, vx6;
        vx3.position.offset_in_place(vector2(rnd.get_random_float(true), rnd.get_random_float(true)));
        vx4.position.offset_in_place(vector2(rnd.get_random_float(true), rnd.get_random_float(true)));
        vx5.position.offset_in_place(vector2(rnd.get_random_float(true), rnd.get_random_float(true)));
        vx6.position.offset_in_place(vector2(rnd.get_random_float(true), rnd.get_random_float(true)));
        frame.add_line(line(vx1, vx2));
        frame.add_line(line(vx3, vx4));
        frame.add_line(line(vx5, vx6));

        auto lines = frame.get_all_modulated_lines(transform2::default_value());
        ASSERT_EQ(lines.size(), static_cast<size_t>(3));

        line expected_ln1(vx1, vx2);
        line expected_ln2(vx3, vx4);
        line expected_ln3(vx5, vx6);
        expected_ln1.apply_transform(transform2::default_value().merge(tform));
        expected_ln2.apply_transform(transform2::default_value().merge(tform));
        expected_ln3.apply_transform(transform2::default_value().merge(tform));

        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln1) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln2) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_ln3) != lines.end());
    }
}

TEST(frame, get_all_modulated_lines_complex)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        // Parent
        frame frame("test_frame");
        // First child
        frame.add_child("child1");
        // Child's child
        frame.get_child("child1")->add_child("child2");

        vector2 pos1(1, 1);
        vector2 scl1(2, 2);
        float rot1 = 0;
        transform2 tform1(pos1, scl1, rot1);

        vector2 pos2(2, 2);
        vector2 scl2(3, 3);
        float rot2 = 90;
        transform2 tform2(pos2, scl2, rot2);

        vector2 pos3(3, 3);
        vector2 scl3(4, 4);
        float rot3 = 180;
        transform2 tform3(pos3, scl3, rot3);

        frame.set_transform(tform1);
        frame.get_child("child1")->set_transform(tform2);
        frame.get_child("child1")->get_child("child2")->set_transform(tform3);

        vertex vx1, vx2, vx3, vx4, vx5, vx6;
        vx3.position.offset_in_place(vector2(1, 1));
        vx4.position.offset_in_place(vector2(2, 2));
        vx5.position.offset_in_place(vector2(3, 3));
        vx6.position.offset_in_place(vector2(4, 4));
        frame.add_line(line(vx1, vx2));
        frame.get_child("child1")->add_line(line(vx3, vx4));
        frame.get_child("child1")->get_child("child2")->add_line(line(vx5, vx6));

        line expected_1 = line(vx1, vx2);
        line expected_2 = line(vx3, vx4);
        line expected_3 = line(vx5, vx6);
        transform2 expected_tform1 = transform2::default_value().merge(tform1);
        transform2 expected_tform2 = transform2::default_value().merge(tform1).merge(tform2);
        transform2 expected_tform3 = transform2::default_value().merge(tform1).merge(tform2).merge(tform3);

        expected_1.apply_transform(expected_tform1);
        expected_2.apply_transform(expected_tform2);
        expected_3.apply_transform(expected_tform3);

        auto lines = frame.get_all_modulated_lines(transform2::default_value());

        ASSERT_EQ(lines.size(), static_cast<size_t>(3));

        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_1) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_2) != lines.end());
        ASSERT_TRUE(std::find(lines.begin(), lines.end(), expected_3) != lines.end());
    }
}

TEST(frame, child_count_shallow)
{
    // Parent
    frame frame("test_frame");

    // First child
    frame.add_child("child1");
    frame.add_child("child2");
    frame.add_child("child3");

    // Child's child
    frame.get_child("child1")->add_child("child11");
    frame.get_child("child1")->add_child("child12");
    frame.get_child("child1")->add_child("child13");
    frame.get_child("child1")->add_child("child14");

    size_t expectedCount = 3;

    size_t count = frame.child_count(false);

    ASSERT_EQ(expectedCount, count);
}

TEST(frame, child_count_deep)
{
    // Parent
    frame frame("test_frame");

    // First child
    frame.add_child("child1");
    frame.add_child("child2");
    frame.add_child("child3");

    // Child's child
    frame.get_child("child1")->add_child("child11");
    frame.get_child("child1")->add_child("child12");
    frame.get_child("child1")->add_child("child13");
    frame.get_child("child1")->add_child("child14");

    size_t expectedCount = 7;

    size_t count = frame.child_count(true);

    ASSERT_EQ(expectedCount, count);
}

