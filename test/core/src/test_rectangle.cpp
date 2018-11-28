#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <rectangle.hpp>

using namespace rvi;

TEST(operator_equality, rectangle)
{
    rectangle a(0,1,2,3);
    rectangle b(0,1,2,3);
    rectangle c(0,1,3,2);

    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a == c);
    ASSERT_FALSE(b == c);
}

TEST(operator_inequality, rectangle)
{
    rectangle a(0, 1, 2, 3);
    rectangle b(0, 1, 2, 3);
    rectangle c(0, 1, 3, 2);

    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
    ASSERT_TRUE(a != c);
    ASSERT_TRUE(b != c);
}

TEST(bounding_methods, rectangle)
{
    rectangle r(2, 4, 7, 11);

    ASSERT_FLOAT_EQ(r.left(), 2);
    ASSERT_FLOAT_EQ(r.right(), 2 + 7);
    ASSERT_FLOAT_EQ(r.bottom(), 4);
    ASSERT_FLOAT_EQ(r.top(), 4 + 11);
}

TEST(corner_methods, rectangle)
{
    rectangle r(2, 4, 7, 11);

    ASSERT_EQ(r.corner_left_bottom(), vector2(2, 4));
    ASSERT_EQ(r.corner_right_bottom(), vector2(2 + 7, 4));
    ASSERT_EQ(r.corner_left_top(), vector2(2, 4 + 11));
    ASSERT_EQ(r.corner_right_top(), vector2(2 + 7, 4 + 11));
}

TEST(contains_point, rectangle)
{
    rectangle r(2, 4, 7, 11);

    vector2 point_a(3, 8);                  // true, arbitrary
    vector2 point_b(2, 4);                  // true, min pos
    vector2 point_c(2 + 7, 4 + 11);         // true, max pos
    vector2 point_d(2 + 7 + 0.01f, 4 + 11); // false, x-coord
    vector2 point_e(2 + 7, 4 + 11 + 0.01f); // false, y-coord

    ASSERT_TRUE(r.contains(point_a));
    ASSERT_TRUE(r.contains(point_b));
    ASSERT_TRUE(r.contains(point_c));
    ASSERT_FALSE(r.contains(point_d));
    ASSERT_FALSE(r.contains(point_e));
}

TEST(contains_rectangle, rectangle)
{
    rectangle r(2, 4, 7, 11);

    rectangle rect_a(2, 4, 7, 11);      // true, same size
    rectangle rect_b(3, 5, 1, 1);       // true, smaller size
    rectangle rect_c(1.99f, 5, 7, 11);  // false, left outside
    rectangle rect_d(2, 5, 7.01f, 11);  // false, right outside
    rectangle rect_e(3, 3.99f, 1, 11);  // false, bottom outside
    rectangle rect_f(3, 4, 1, 11.01f);  // false, top outside

    ASSERT_TRUE(r.contains(rect_a));
    ASSERT_TRUE(r.contains(rect_b));
    ASSERT_FALSE(r.contains(rect_c));
    ASSERT_FALSE(r.contains(rect_d));
    ASSERT_FALSE(r.contains(rect_e));
    ASSERT_FALSE(r.contains(rect_f));
}

TEST(intersects_rectangle, rectangle)
{
    rectangle r(2, 4, 7, 11);

    rectangle rect_a(2, 4, 7, 11);      // true, same size
    rectangle rect_b(3, 5, 1, 1);       // true, smaller size
    rectangle rect_c(1, 3, 8, 12);      // true, larger size
    rectangle rect_d(1, 4, 6, 11);      // true, right corner just touches
    rectangle rect_e(1, 4, 0.99f, 1);   // false, right corner outside
    rectangle rect_f(3, 5, 1, 12);      // true, vertical overlap
    rectangle rect_g(2 - 7.01f, 4 - 11.01f, 7, 11);         // false, same size but outside of range
    rectangle rect_h(2 - 6.99f, 4 - 10.99f, 7, 11);         // true, just by 0.01f
    rectangle rect_i(2 - 7.00f, 4 - 11.00f, 7, 11);         // true, minimum overlap

    ASSERT_TRUE(r.intersects(rect_a));
    ASSERT_TRUE(r.intersects(rect_b));
    ASSERT_TRUE(r.intersects(rect_c));
    ASSERT_TRUE(r.intersects(rect_d));
    ASSERT_FALSE(r.intersects(rect_e));
    ASSERT_TRUE(r.intersects(rect_f));
    ASSERT_FALSE(r.intersects(rect_g));
    ASSERT_TRUE(r.intersects(rect_h));
    ASSERT_TRUE(r.intersects(rect_i));
}