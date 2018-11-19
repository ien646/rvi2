#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>

#include <reader.hpp>

using namespace rvi;

TEST(reader, process_text)
{
    std::ifstream ifs("test_program.rpf");
    reader rdr(ifs);
    auto result = rdr.process();
    return;
}