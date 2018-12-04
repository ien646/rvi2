#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <serialization_base.hpp>

TEST(serialization_base_roundtrips, float_32)
{
    float a = 0.0F;
    float b = 1.3700101F;
    float c = NAN;
    float d = INFINITY;
    float e = std::numeric_limits<float>::max();
    float f = std::numeric_limits<float>::lowest();

    rvi::data_t data;
    rvi::serialize_fp32_bf(data, a);
    rvi::serialize_fp32_bf(data, b);
    rvi::serialize_fp32_bf(data, c);
    rvi::serialize_fp32_bf(data, d);
    rvi::serialize_fp32_bf(data, e);
    rvi::serialize_fp32_bf(data, f);

    ASSERT_TRUE(data.size() == sizeof(float) * 6);
    
    float da, db, dc, dd, de, df;
    da = rvi::deserialize_fp32(data, (0 * sizeof(float)));
    db = rvi::deserialize_fp32(data, (1 * sizeof(float)));
    dc = rvi::deserialize_fp32(data, (2 * sizeof(float)));
    dd = rvi::deserialize_fp32(data, (3 * sizeof(float)));
    de = rvi::deserialize_fp32(data, (4 * sizeof(float)));
    df = rvi::deserialize_fp32(data, (5 * sizeof(float)));

    ASSERT_FLOAT_EQ(da, a);
    ASSERT_FLOAT_EQ(db, b);
    ASSERT_TRUE(std::isnan(dc));
    ASSERT_TRUE(std::isinf(dd));
    ASSERT_FLOAT_EQ(de, e);
    ASSERT_FLOAT_EQ(df, f);
}

TEST(serialization_base_roundtrips, float_64)
{
    double a = 0.0;
    double b = 1.3700101;
    double c = NAN;
    double d = INFINITY;

    rvi::data_t data;
    rvi::serialize_fp64_bf(data, a);
    rvi::serialize_fp64_bf(data, b);
    rvi::serialize_fp64_bf(data, c);
    rvi::serialize_fp64_bf(data, d);

    ASSERT_TRUE(data.size() == sizeof(double) * 4);
    
    double da, db, dc, dd;
    da = rvi::deserialize_fp64(data, (0 * sizeof(double)));
    db = rvi::deserialize_fp64(data, (1 * sizeof(double)));
    dc = rvi::deserialize_fp64(data, (2 * sizeof(double)));
    dd = rvi::deserialize_fp64(data, (3 * sizeof(double)));

    ASSERT_DOUBLE_EQ(da, a);
    ASSERT_DOUBLE_EQ(db, b);
    ASSERT_TRUE(std::isnan(dc));
    ASSERT_TRUE(std::isinf(dd));
}