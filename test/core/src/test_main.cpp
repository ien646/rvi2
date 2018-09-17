#include "gtest/gtest.h"
#include <iostream>

#if defined(__DATE__) && defined(__TIME__)
#define RVI_PRINT_TIMESTAMP() std::cout << std::endl << " # Tests compilation date: " << __DATE__ << " | " << __TIME__ << std::endl
#else
#define RVI_PRINT_TIMESTAMP() std::cout << "Compilation datetime unavailable (Op. not supported)" << std::endl
#endif

int main(int argc, char **argv)
{    
    RVI_PRINT_TIMESTAMP();
    testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS();
    RVI_PRINT_TIMESTAMP();

    std::cout << "Press Enter to exit..." << std::endl;
    return std::getchar();    
}