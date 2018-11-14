#include <gtest/gtest.h>

#include <vector2.hpp>
#include <transform2.hpp>
#include "random_gen.hpp"

#include <cmath>

static const int OP_TEST_ITER = 500;
static random_gen rnd;

using rvi::vector2;

//////////////////////////////////////////////////////////////////////////
// OPERATORS
//////////////////////////////////////////////////////////////////////////

TEST (vector_operators, add)
{
    float acc_x = 0;
    float acc_y = 0;

    vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();

        vector2 vec(x, y);

        result += vec;

        acc_x += x;
        acc_y += y;
    }

    ASSERT_FLOAT_EQ(result.x, acc_x);
    ASSERT_FLOAT_EQ(result.y, acc_y);
}

TEST (vector_operators, sub)
{
	float acc_x = 0;
    float acc_y = 0;

    vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();

        vector2 vec(x, y);

        result -= vec;

        acc_x -= x;
        acc_y -= y;
    }
    
    ASSERT_FLOAT_EQ(result.x, acc_x);
    ASSERT_FLOAT_EQ(result.y, acc_y);
}

TEST (vector_operators, multiply_scalar_op)
{
	float acc_x = 0;
    float acc_y = 0;

    vector2 result(0, 0);
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float mul = rnd.get_random_float();

        result *= mul;

        acc_x *= mul;
        acc_y *= mul;
    }

    ASSERT_FLOAT_EQ(result.x, acc_x);
    ASSERT_FLOAT_EQ(result.y, acc_y);
}

TEST (vector_operators, divide_scalar_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();        

        vector2 vec(x, y);

        float scale = rnd.get_random_float(true);

        vec /= scale;

        ASSERT_FLOAT_EQ(vec.x, (x / scale));
        ASSERT_FLOAT_EQ(vec.y, (y / scale));
    }
}

TEST (vector_operators, multiply_cross_op)
{
    float acc_x = 0;
    float acc_y = 0;

    vector2 result(0, 0);
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();

        vector2 vec(x, y);

        result *= vec;

        acc_x *= x;
        acc_y *= y;
    }

    ASSERT_FLOAT_EQ(result.x, acc_x);
    ASSERT_FLOAT_EQ(result.y, acc_y);
}

TEST (vector_operators, equality_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 a(rnd.get_random_float(), rnd.get_random_float());
        vector2 b(a.x, a.y);
        vector2 c(rnd.get_random_float(), rnd.get_random_float());

        ASSERT_TRUE(a == b);
        ASSERT_FALSE(a == c);
    }
}

TEST (vector_operators, inequality_op)
{
    for(int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 a(rnd.get_random_float(), rnd.get_random_float());
        vector2 b(a.x, a.y);
        vector2 c(rnd.get_random_float(), rnd.get_random_float());

        ASSERT_FALSE(a != b);
        ASSERT_TRUE(a != c);
    }
}

//////////////////////////////////////////////////////////////////////////
// METHODS
//////////////////////////////////////////////////////////////////////////

TEST (vector_methods, magnitude)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        vector2 vec(rnd.get_random_float(), rnd.get_random_float());        
        float manualMagnitude = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
        ASSERT_FLOAT_EQ(manualMagnitude, vec.magnitude());
    }
}

TEST (vector_methods, offset)
{    
    float acc_x = 0;
    float acc_y = 0;
    vector2 result(0, 0);
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        acc_x += x;
        acc_y += y;
        vector2 offs(x, y);       
        result = result.offset(offs);
    }

    ASSERT_FLOAT_EQ(result.x, acc_x);
    ASSERT_FLOAT_EQ(result.y, acc_y);
}

TEST (vector_methods, offset_in_place)
{
    float acc_x = 0;
    float acc_y = 0;
    vector2 result(0, 0);
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        acc_x += x;
        acc_y += y;
        vector2 offs(x, y);
        result.offset_in_place(offs);
    }

    ASSERT_FLOAT_EQ(result.x, acc_x);
    ASSERT_FLOAT_EQ(result.y, acc_y);
}

TEST (vector_methods, Rotate)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float mag = rnd.get_random_float();
        vector2 vec(mag, 0);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.x, vec.y);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.x, 0.0F);
        ASSERT_FLOAT_EQ(vec.y, mag);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(-vec.x, vec.y);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.x, -mag);
        ASSERT_FLOAT_EQ(vec.y, 0.0F);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(-vec.x, -vec.y);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.x, 0.0F);
        ASSERT_FLOAT_EQ(vec.y, -mag);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.x, -vec.y);

        vec = vec.rotate(45.0F);
        ASSERT_FLOAT_EQ(vec.x, mag);
        ASSERT_FLOAT_EQ(vec.y, 0.0F);
    }
}

TEST (vector_methods, rotate_in_place)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float mag = rnd.get_random_float();
        vector2 vec(mag, 0);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(vec.x, vec.y);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(vec.x, 0.0F);
        ASSERT_FLOAT_EQ(vec.y, mag);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(-vec.x, vec.y);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(vec.x, -mag);
        ASSERT_FLOAT_EQ(vec.y, 0.0F);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(-vec.x, -vec.y);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(vec.x, 0.0F);
        ASSERT_FLOAT_EQ(vec.y, -mag);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(vec.x, -vec.y);

        vec.rotate_in_place(45.0F);
        ASSERT_FLOAT_EQ(vec.x, mag);
        ASSERT_FLOAT_EQ(vec.y, 0.0F);
    }
}

TEST (vector_methods, reverse)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        vec = vec.reverse();

        ASSERT_FLOAT_EQ(-x, vec.x);
        ASSERT_FLOAT_EQ(-y, vec.y);
    }
}

TEST (vector_methods, reverse_in_place)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        vec.reverse_in_place();

        ASSERT_FLOAT_EQ(-x, vec.x);
        ASSERT_FLOAT_EQ(-y, vec.y);
    }
}

TEST (vector_methods, scale_scalar)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        float scale = rnd.get_random_float();

        vec = vec.scale(scale);

        ASSERT_FLOAT_EQ(x * scale, vec.x);
        ASSERT_FLOAT_EQ(y * scale, vec.y);
    }
}

TEST (vector_methods, scale_cross)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        float scale_x = rnd.get_random_float();
        float scale_y = rnd.get_random_float();
        vector2 scale(scale_x, scale_y);

        vec = vec.scale(scale);

        ASSERT_FLOAT_EQ(x * scale_x, vec.x);
        ASSERT_FLOAT_EQ(y * scale_y, vec.y);
    }
}

TEST (vector_methods, scale_in_place_scalar)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        float scale = rnd.get_random_float();

        vec.scale_in_place(scale);

        ASSERT_FLOAT_EQ(x * scale, vec.x);
        ASSERT_FLOAT_EQ(y * scale, vec.y);
    }
}

TEST (vector_methods, scale_in_place_cross)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        float scale_x = rnd.get_random_float();
        float scale_y = rnd.get_random_float();
        vector2 scale(scale_x, scale_y);

        vec.scale_in_place(scale);

        ASSERT_FLOAT_EQ(x * scale_x, vec.x);
        ASSERT_FLOAT_EQ(y * scale_y, vec.y);
    }
}

TEST (vector_methods, invert)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float();
        float y = rnd.get_random_float();
        vector2 vec(x, y);

        vec = vec.invert();

        ASSERT_FLOAT_EQ((1.0F / x), vec.x);
        ASSERT_FLOAT_EQ((1.0F / y), vec.y);
    }
}

TEST (vector_methods, invert_in_place)
{
    for (int i = 0; i < OP_TEST_ITER; i++)
    {
        float x = rnd.get_random_float(true);
        float y = rnd.get_random_float(true);
        vector2 vec(x, y);

        vec.invert_in_place();

        ASSERT_FLOAT_EQ((1.0F / x), vec.x);
        ASSERT_FLOAT_EQ((1.0F / y), vec.y);
    }
}