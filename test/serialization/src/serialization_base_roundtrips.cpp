#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

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

template<typename T>
static void test_serialize_integral()
{
    std::cout   << "  >> Testing integral: [" 
                << typeid(T).name()
                << "]"
                << std::endl;

    T arr[] = 
    {
        std::numeric_limits<T>::max(),
        std::numeric_limits<T>::min(),
        std::numeric_limits<T>::max() / 2,
        std::numeric_limits<T>::min() / 2,
        static_cast<T>(0)
    };

    rvi::data_t buff;
    for(T v : arr)
    {
        rvi::serialize_integral<T>(buff, v);
    }   

    int arr_len = sizeof(arr) / sizeof(T);
    ASSERT_TRUE(buff.size() == sizeof(arr));

    for(int i = 0; i < arr_len; ++i)
    {
        int offset = i * sizeof(T);
        T dval = rvi::deserialize_integral<T>(buff, offset);
        ASSERT_EQ(arr[i], dval);
    }
}

TEST(serialization_base_roundtrips, integers)
{
    test_serialize_integral<uint8_t>();
    test_serialize_integral<uint16_t>();
    test_serialize_integral<uint32_t>();
    test_serialize_integral<uint64_t>();

    test_serialize_integral<int8_t>();
    test_serialize_integral<int16_t>();
    test_serialize_integral<int32_t>();
    test_serialize_integral<int64_t>();

    test_serialize_integral<char>();
    test_serialize_integral<short>();
    test_serialize_integral<int>();
    test_serialize_integral<long>();
    test_serialize_integral<long long>();

    test_serialize_integral<unsigned char>();
    test_serialize_integral<unsigned short>();
    test_serialize_integral<unsigned int>();
    test_serialize_integral<unsigned long>();
    test_serialize_integral<unsigned long long>();
}

TEST(serialization_base_roundtrips, color_rgba)
{
    rvi::color_rgba a(0, 0, 0, 0);
    rvi::color_rgba b(127, 127, 127, 127);
    rvi::color_rgba c(255, 255, 255, 255);

    rvi::data_t buff;
    rvi::serialize_color_rgba_bf(buff, a);
    rvi::serialize_color_rgba_bf(buff, b);
    rvi::serialize_color_rgba_bf(buff, c);

    const int crgba_size = 4;

    ASSERT_TRUE(buff.size() == 3 * crgba_size);

    int offset = 0;
    rvi::color_rgba da, db, dc;
    da = rvi::deserialize_color_rgba(buff, offset);
    offset += crgba_size;

    db = rvi::deserialize_color_rgba(buff, offset);
    offset += crgba_size;

    dc = rvi::deserialize_color_rgba(buff, offset);
    offset += crgba_size;

    ASSERT_TRUE(a == da);
    ASSERT_TRUE(b == db);
    ASSERT_TRUE(c == dc);
}

TEST(serialization_base_roundtrips, vector2)
{
    rvi::vector2 a(0.0F, 0.0F);
    rvi::vector2 b(-1.0F, -1.0F);
    rvi::vector2 c(1.0F, 1.0F);
    rvi::vector2 d(0.51F, 1.13F);

    rvi::data_t buff;
    rvi::serialize_vector2_bf(buff, a);
    rvi::serialize_vector2_bf(buff, b);
    rvi::serialize_vector2_bf(buff, c);
    rvi::serialize_vector2_bf(buff, d);

    ASSERT_TRUE(buff.size() == (sizeof(float) * 2) * 4);

    rvi::vector2 da, db, dc, dd;
    da = rvi::deserialize_vector2(buff, 0);
    db = rvi::deserialize_vector2(buff, 8);
    dc = rvi::deserialize_vector2(buff, 16);
    dd = rvi::deserialize_vector2(buff, 24);

    ASSERT_TRUE(da == a);
    ASSERT_TRUE(db == b);
    ASSERT_TRUE(dc == c);
    ASSERT_TRUE(dd == d);
}

TEST(serialization_base_roundtrips, vertex)
{
    rvi::vertex a(rvi::vector2(0.0F, 0.0F), rvi::color_rgba(0, 0, 0, 0));
    rvi::vertex b(rvi::vector2(1.0F, 1.0F), rvi::color_rgba(10, 20, 50, 100));
    rvi::vertex c(rvi::vector2(0.33F, 0.111F), rvi::color_rgba(111, 222, 71, 212));

    rvi::data_t buff;
    rvi::serialize_vertex_bf(buff, a);
    rvi::serialize_vertex_bf(buff, b);
    rvi::serialize_vertex_bf(buff, c);

    ASSERT_TRUE(buff.size() == 3 * 12);

    rvi::vertex da, db, dc;
    da = rvi::deserialize_vertex(buff, 0);
    db = rvi::deserialize_vertex(buff, 12);
    dc = rvi::deserialize_vertex(buff, 24);

    ASSERT_TRUE(a == da);
    ASSERT_TRUE(b == db);
    ASSERT_TRUE(c == dc);
}
