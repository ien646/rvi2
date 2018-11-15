#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <str_utils.hpp>

TEST(str_utils, split)
{
    std::string test_str = "12345,abcde,*/*+-";
    auto segments = rvi::str_utils::split(test_str, ',');

    ASSERT_EQ(segments[0], "12345");
    ASSERT_EQ(segments[1], "abcde");
    ASSERT_EQ(segments[2], "*/*+-");
}

TEST(str_utils, split_once_beg)
{
    std::string test_str = "12345,abcde,*/*+-";
    auto pair = rvi::str_utils::split_once_beg(test_str, ',');

    ASSERT_EQ(pair.first, "12345");
    ASSERT_EQ(pair.second, "abcde,*/*+-");
}

TEST(str_utils, split_once_end)
{
    std::string test_str = "12345,abcde,*/*+-";
    auto pair = rvi::str_utils::split_once_end(test_str, ',');

    ASSERT_EQ(pair.first, "12345,abcde");
    ASSERT_EQ(pair.second, "*/*+-");
}

TEST(str_utils, substr_from_delim)
{
    std::string test_str = "12345,abcde,*/*+-";
    auto res = rvi::str_utils::substr_from_delim(test_str, ',');
    
    ASSERT_EQ(res, "abcde,*/*+-");
}

TEST(str_utils, substr_until_delim)
{
    std::string test_str = "12345,abcde,*/*+-";
    auto res = rvi::str_utils::substr_until_delim(test_str, ',');

    ASSERT_EQ(res, "12345");
}

TEST(str_utils, trim_ws_beg)
{
    std::string test_str = "  dfas- adsf ;lj;    ";
    auto res = rvi::str_utils::trim_ws_beg(test_str);

    ASSERT_EQ(res, "dfas- adsf ;lj;    ");
}

TEST(str_utils, trim_ws_end)
{
    std::string test_str = "  dfas- adsf ;lj;    ";
    auto res = rvi::str_utils::trim_ws_end(test_str);
    ASSERT_EQ(res, "  dfas- adsf ;lj;");
}

TEST(str_utils, trim_ws)
{
    std::string test_str = "  dfas- adsf ;lj;    ";
    auto res = rvi::str_utils::trim_ws(test_str);
    ASSERT_EQ(res, "dfas- adsf ;lj;");
}

TEST(str_utils, replace_char)
{
    std::string test_str = "e abcdefgh-eee-bebe e";
    auto res = rvi::str_utils::replace(test_str, 'e', 'x');
    ASSERT_EQ(res, "x abcdxfgh-xxx-bxbx x");
}

TEST(str_utils, replace_string)
{
    std::string test_str = "123-124-421-421123 123";

    std::string a = "123";
    std::string b = "abcde";
    std::string c = "";
    auto res = rvi::str_utils::replace(test_str, a, b);
    ASSERT_EQ(res, "abcde-124-421-421abcde abcde");
    
    res = rvi::str_utils::replace(res, b, c);
    ASSERT_EQ(res, "-124-421-421 ");
}