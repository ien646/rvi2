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

