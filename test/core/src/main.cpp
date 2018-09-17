#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS();
    int aux = 0;
    std::cin >> aux;
    return 0;
}