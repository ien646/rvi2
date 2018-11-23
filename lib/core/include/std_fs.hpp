#pragma once

#if defined __GNUC__
    #if defined __llvm__ || defined __clang__ 
    // -- CLANG
        #if __clang_major__ >= 7
            #include <filesystem>
        #elif __clang_major__ >= 6
            #include <experimental/filesystem>
        #else
            #error At least Clang version 6.x is required for <filesystem> support!
        #endif
    #else
    // -- GCC
        #if __GNUC__ >= 8
            #include <filesystem>
        #elif __GNUC__ >= 7
            #include <experimental/filesystem>
        #else
            #error At least GCC version 7.x is required for <filesystem> support!
        #endif
    #endif
#elif _MSC_VER && !__INTEL_COMPILER // -- MSVC
    #if _MSC_VER >= 1911 // VS 2017
        #include <filesystem>
    #elif _MSC_VER >= 1900 // VS 2015
        #include <experimental/filesystem>
    #else
        #error At least version 1900 of MSVC (VS 2015) is required for <filesystem> support!
    #endif
#elif __INTEL_COMPILER
    #if __INTEL_COMPILER >= 1900
        #include <filesystem>
    #elif __INTEL_COMPILER >= 1800
        #include <experimental/filesystem>
    #else
        #error At least version 1800 of Intel C/C++ Compiler (18.0.0) is required for <filesystem> support!
    #endif
#endif