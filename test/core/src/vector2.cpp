#include "gtest/gtest.h"
#include "vector2.hpp"

#include <random>
#include <ctime>

static const int OP_TEST_ITER = 99999;

static std::mt19937 Rand_Generator(static_cast<int>(time(0)));

static std::uniform_real_distribution<float> Rand_Dist_Float(
    std::numeric_limits<float>::min(), std::numeric_limits<float>::max());

static std::uniform_int_distribution<int> Rand_Dist_Int(
    std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

using rvi::Vector2;

static float GetRandomFloat()
{
    return Rand_Dist_Float(Rand_Generator);
}

static int GetRandomInt()
{    
    return Rand_Dist_Int(Rand_Generator);
}

TEST (VectorOperators, Add)
{
    float acc_x = 0;
    float acc_y = 0;

    Vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();

        Vector2 vec(x, y);

        result += vec;

        acc_x += x;
        acc_y += y;
    }

    ASSERT_EQ(result.X, acc_x);
    ASSERT_EQ(result.Y, acc_y);
}

TEST (VectorOperators, Sub)
{
	float acc_x = 0;
    float acc_y = 0;

    Vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();

        Vector2 vec(x, y);

        result -= vec;

        acc_x -= x;
        acc_y -= y;
    }

    ASSERT_EQ(result.X, acc_x);
    ASSERT_EQ(result.Y, acc_y);
}

TEST (VectorOperators, Multiply)
{
	float acc_x = 0;
    float acc_y = 0;

    Vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();

        Vector2 vec(x, y);

        result *= vec;

        acc_x *= x;
        acc_y *= y;
    }

    ASSERT_EQ(result.X, acc_x);
    ASSERT_EQ(result.Y, acc_y);
}

TEST (VectorOperators, Divide)
{
	float acc_x = 0;
    float acc_y = 0;

    Vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();

        Vector2 vec(x, y);

        result /= vec;

        acc_x /= x;
        acc_y /= y;
    }

    ASSERT_EQ(result.X, acc_x);
    ASSERT_EQ(result.Y, acc_y);
}

TEST (VectorOperators, Equality)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 a(GetRandomFloat(), GetRandomFloat());
        Vector2 b(a.X, a.Y);
        Vector2 c(GetRandomFloat(), GetRandomFloat());

        ASSERT_TRUE(a == b);
        ASSERT_FALSE(a == c);
    }
}

TEST (VectorOperators, Inequality)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 a(GetRandomFloat(), GetRandomFloat());
        Vector2 b(a.X, a.Y);
        Vector2 c(GetRandomFloat(), GetRandomFloat());

        ASSERT_FALSE(a != b);
        ASSERT_TRUE(a != c);
    }
}