#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

int main(int argc, char **argv)
{    
    testing::InitGoogleTest(&argc, argv); 
    testing::InitGoogleMock(&argc, argv);
    RUN_ALL_TESTS();    

    std::cout << "Press Enter to exit..." << std::endl;
    return std::getchar();    
}