#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{    
    testing::InitGoogleTest(&argc, argv); 
    testing::InitGoogleMock(&argc, argv);   

    int result = RUN_ALL_TESTS();

    std::this_thread::sleep_for(1500ms);

    return result;
}