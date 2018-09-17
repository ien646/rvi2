#include "gtest/gtest.h"
#include "vector2.hpp"

TEST (VectorAdd, VectorOperators)
{
	rvi::Vector2 v1(5, 10);
    rvi::Vector2 v2(6, 12);
    ASSERT_EQ((v1+v2), rvi::Vector2(11, 22));
}

TEST (VectorSub, VectorOperators)
{
	rvi::Vector2 v1(7, 77);
    rvi::Vector2 v2(1, -5);
    ASSERT_EQ((v1+v2), rvi::Vector2(8, 72));
}