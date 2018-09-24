#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <transform2.hpp>

#include "random_gen.hpp"

using namespace rvi;

static const int OP_TEST_ITER = 5000;

TEST(transform2, merge)
{
    vector2 offset1(get_random_float(), get_random_float());
    vector2 scale1(get_random_float(), get_random_float());
    float rot1 = get_random_float();

    vector2 offset2(get_random_float(), get_random_float());
    vector2 scale2(get_random_float(), get_random_float());
    float rot2 = get_random_float();

    transform2 tform1(offset1, scale1, rot1);
    transform2 tform2(offset2, scale2, rot2);

    transform2 finalTform = tform1.merge(tform2);

    transform2 expectedTform((offset1 + offset2), (scale1 * scale2), (math::clamp_angle_deg(rot1 + rot2)));

    ASSERT_EQ(finalTform, expectedTform);
}

TEST(transform2, merge_in_place)
{
    vector2 offset1(get_random_float(), get_random_float());
    vector2 scale1(get_random_float(), get_random_float());
    float rot1 = get_random_float();

    vector2 offset2(get_random_float(), get_random_float());
    vector2 scale2(get_random_float(), get_random_float());
    float rot2 = get_random_float();

    transform2 tform1(offset1, scale1, rot1);
    transform2 tform2(offset2, scale2, rot2);

    tform1.merge_in_place(tform2);

    transform2 expectedTform((offset1 + offset2), (scale1 * scale2), (math::clamp_angle_deg(rot1 + rot2)));

    ASSERT_EQ(tform1, expectedTform);
}

TEST(transform2, equality_op)
{
    vector2 offset1(get_random_float(), get_random_float());
    vector2 scale1(get_random_float(), get_random_float());
    float rot1 = get_random_float();

    vector2 offset2(get_random_float(), get_random_float());
    vector2 scale2(get_random_float(), get_random_float());
    float rot2 = get_random_float();

    transform2 tform1(offset1, scale1, rot1);
    transform2 tform2(offset1, scale1, rot1);
    transform2 tform3(offset2, scale2, rot2);

    ASSERT_TRUE(tform1 == tform2);
    ASSERT_FALSE(tform1 == tform3);
}

TEST(transform2, inequality_op)
{
    vector2 offset1(get_random_float(), get_random_float());
    vector2 scale1(get_random_float(), get_random_float());
    float rot1 = get_random_float();

    vector2 offset2(get_random_float(), get_random_float());
    vector2 scale2(get_random_float(), get_random_float());
    float rot2 = get_random_float();

    transform2 tform1(offset1, scale1, rot1);
    transform2 tform2(offset1, scale1, rot1);
    transform2 tform3(offset2, scale2, rot2);

    ASSERT_FALSE(tform1 != tform2);
    ASSERT_TRUE(tform1 != tform3);
}