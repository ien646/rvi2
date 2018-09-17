#include "gtest/gtest.h"
#include "vector2.hpp"

#include <random>
#include <ctime>
#include <cmath>


static const int OP_TEST_ITER = 99999;

static std::mt19937 Rand_Generator(static_cast<int>(time(0)));

static std::uniform_real_distribution<float> Rand_Dist_Float(
    -1000.0F, 1000.0F);

static std::uniform_int_distribution<int> Rand_Dist_Int(
    -1000, 1000);

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

    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
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
    
    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
}

TEST (VectorOperators, MultiplyScalar)
{
	float acc_x = 0;
    float acc_y = 0;

    Vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float mul = GetRandomFloat();

        result *= mul;

        acc_x *= mul;
        acc_y *= mul;
    }

    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
}

TEST (VectorOperators, DivideScalar)
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

    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
}

TEST(VectorOperators, MultiplyCrossProduct)
{
    float acc_x = 0;
    float acc_y = 0;

    Vector2 result(0, 0);
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();

        Vector2 vec(x, y);

        result *= vec;

        acc_x *= x;
        acc_y *= y;
    }

    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
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

TEST(VectorFunctions, Magnitude)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        Vector2 vec(GetRandomFloat(), GetRandomFloat());        
        float manualMagnitude = std::sqrtf(std::powf(vec.X, 2) + std::powf(vec.Y, 2));
        ASSERT_FLOAT_EQ(manualMagnitude, vec.Magnitude());
    }
}

TEST(VectorFunctions, Offset)
{    
    float acc_x = 0;
    float acc_y = 0;
    Vector2 result(0, 0);
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();
        acc_x += x;
        acc_y += y;
        Vector2 offs(x, y);       
        result = result.Offset(offs);
    }

    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
}

TEST(VectorFunctions, OffsetInPlace)
{
    float acc_x = 0;
    float acc_y = 0;
    Vector2 result(0, 0);
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();
        acc_x += x;
        acc_y += y;
        Vector2 offs(x, y);
        result.OffsetInPlace(offs);
    }

    ASSERT_FLOAT_EQ(result.X, acc_x);
    ASSERT_FLOAT_EQ(result.Y, acc_y);
}

TEST(VectorFunctions, Rotate)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float mag = GetRandomFloat();
        Vector2 vec(mag, 0);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.X, vec.Y);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.X, 0.0F);
        ASSERT_FLOAT_EQ(vec.Y, mag);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(-vec.X, vec.Y);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.X, -mag);
        ASSERT_FLOAT_EQ(vec.Y, 0.0F);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(-vec.X, -vec.Y);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.X, 0.0F);
        ASSERT_FLOAT_EQ(vec.Y, -mag);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.X, -vec.Y);

        vec = vec.Rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.X, mag);
        ASSERT_FLOAT_EQ(vec.Y, 0.0F);
    }
}

TEST(VectorFunctions, RotateInPlace)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float mag = GetRandomFloat();
        Vector2 vec(mag, 0);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(vec.X, vec.Y);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(vec.X, 0.0F);
        ASSERT_FLOAT_EQ(vec.Y, mag);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(-vec.X, vec.Y);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(vec.X, -mag);
        ASSERT_FLOAT_EQ(vec.Y, 0.0F);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(-vec.X, -vec.Y);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(vec.X, 0.0F);
        ASSERT_FLOAT_EQ(vec.Y, -mag);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(vec.X, -vec.Y);

        vec.RotateInPlace(45.0F);
        ASSERT_FLOAT_EQ(vec.X, mag);
        ASSERT_FLOAT_EQ(vec.Y, 0.0F);
    }
}

TEST(VectorFunctions, Reverse)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();
        Vector2 vec(x, y);

        vec = vec.Reverse();

        ASSERT_FLOAT_EQ(-x, vec.X);
        ASSERT_FLOAT_EQ(-y, vec.Y);
    }
}

TEST(VectorFunctions, ReverseInPlace)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = GetRandomFloat();
        float y = GetRandomFloat();
        Vector2 vec(x, y);

        vec.ReverseInPlace();

        ASSERT_FLOAT_EQ(-x, vec.X);
        ASSERT_FLOAT_EQ(-y, vec.Y);
    }
}