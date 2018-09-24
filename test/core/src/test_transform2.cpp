#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <transform2.hpp>

#include "random_gen.hpp"

using namespace rvi;

static const int OP_TEST_ITER = 5000;

TEST(Transform2, Merge)
{
    Vector2 offset1(GetRandomFloat(), GetRandomFloat());
    Vector2 scale1(GetRandomFloat(), GetRandomFloat());
    float rot1 = GetRandomFloat();

    Vector2 offset2(GetRandomFloat(), GetRandomFloat());
    Vector2 scale2(GetRandomFloat(), GetRandomFloat());
    float rot2 = GetRandomFloat();

    Transform2 tform1(offset1, scale1, rot1);
    Transform2 tform2(offset2, scale2, rot2);

    Transform2 finalTform = tform1.Merge(tform2);

    Transform2 expectedTform((offset1 + offset2), (scale1 * scale2), (Math::ClampAngleDeg(rot1 + rot2)));

    ASSERT_EQ(finalTform, expectedTform);
}

TEST(Transform2, MergeInPlace)
{
    Vector2 offset1(GetRandomFloat(), GetRandomFloat());
    Vector2 scale1(GetRandomFloat(), GetRandomFloat());
    float rot1 = GetRandomFloat();

    Vector2 offset2(GetRandomFloat(), GetRandomFloat());
    Vector2 scale2(GetRandomFloat(), GetRandomFloat());
    float rot2 = GetRandomFloat();

    Transform2 tform1(offset1, scale1, rot1);
    Transform2 tform2(offset2, scale2, rot2);

    tform1.MergeInPlace(tform2);

    Transform2 expectedTform((offset1 + offset2), (scale1 * scale2), (Math::ClampAngleDeg(rot1 + rot2)));

    ASSERT_EQ(tform1, expectedTform);
}

TEST(Transform2, EqualityOperator)
{
    Vector2 offset1(GetRandomFloat(), GetRandomFloat());
    Vector2 scale1(GetRandomFloat(), GetRandomFloat());
    float rot1 = GetRandomFloat();

    Vector2 offset2(GetRandomFloat(), GetRandomFloat());
    Vector2 scale2(GetRandomFloat(), GetRandomFloat());
    float rot2 = GetRandomFloat();

    Transform2 tform1(offset1, scale1, rot1);
    Transform2 tform2(offset1, scale1, rot1);
    Transform2 tform3(offset2, scale2, rot2);

    ASSERT_TRUE(tform1 == tform2);
    ASSERT_FALSE(tform1 == tform3);
}

TEST(Transform2, InequalityOperator)
{
    Vector2 offset1(GetRandomFloat(), GetRandomFloat());
    Vector2 scale1(GetRandomFloat(), GetRandomFloat());
    float rot1 = GetRandomFloat();

    Vector2 offset2(GetRandomFloat(), GetRandomFloat());
    Vector2 scale2(GetRandomFloat(), GetRandomFloat());
    float rot2 = GetRandomFloat();

    Transform2 tform1(offset1, scale1, rot1);
    Transform2 tform2(offset1, scale1, rot1);
    Transform2 tform3(offset2, scale2, rot2);

    ASSERT_FALSE(tform1 != tform2);
    ASSERT_TRUE(tform1 != tform3);
}