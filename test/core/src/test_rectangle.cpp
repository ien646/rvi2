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
    rectangle a(0,1,2,3);
    rectangle b(0,1,2,3);
    rectangle c(0,1,3,2);

    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
    ASSERT_TRUE(a != c);
    ASSERT_TRUE(b != c);
}