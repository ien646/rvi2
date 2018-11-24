#pragma once

/*
 * Including this file is equivalent to issuing a "#include <filesystem>", but
 * it takes care of compiler and compiler-version checking to avoid obscure issues
 * during the build process
**/

#undef RVI_HAS_STD_FILESYSTEM
#undef RVI_HAS_STD_FILESYSTEM_EXPERIMENTAL

#if defined __GNUC__ && !__INTEL_COMPILER
    #if defined __llvm__ || defined __clang__ 
    // -- CLANG
        #if __clang_major__ >= 7
            #include <filesystem>
            #define RVI_HAS_STD_FILESYSTEM
        #elif __clang_major__ >= 6
            #include <experimental/filesystem>
            #define RVI_HAS_STD_FILESYSTEM
            #define RVI_HAS_STD_FILESYSTEM_EXPERIMENTAL
        #else
            #warning At least Clang version 6.x is required for <filesystem> support!
        #endif
    #else
    // -- GCC
        #if __GNUC__ >= 8
            #include <filesystem>
            #define RVI_HAS_STD_FILESYSTEM
        #elif __GNUC__ >= 7
            #include <experimental/filesystem>
            #define RVI_HAS_STD_FILESYSTEM
            #define RVI_HAS_STD_FILESYSTEM_EXPERIMENTAL
        #else
            #warning At least GCC version 7.x is required for <filesystem> support!
        #endif
    #endif
#elif _MSC_VER && !__INTEL_COMPILER // -- MSVC
    #if _MSC_VER >= 1911 // VS 2017
        #include <filesystem>
        #define RVI_HAS_STD_FILESYSTEM
    #elif _MSC_VER >= 1900 // VS 2015
        #include <experimental/filesystem>
        #define RVI_HAS_STD_FILESYSTEM
        #define RVI_HAS_STD_FILESYSTEM_EXPERIMENTAL
    #else
        #warning At least version 1900 of MSVC (VS 2015) is required for <filesystem> support!
    #endif
#elif __INTEL_COMPILER
    #if __INTEL_COMPILER >= 1900
        #include <filesystem>
        #define RVI_HAS_STD_FILESYSTEM
    #elif __INTEL_COMPILER >= 1800
        #include <experimental/filesystem>
        #define RVI_HAS_STD_FILESYSTEM
        #define RVI_HAS_STD_FILESYSTEM_EXPERIMENTAL
    #else
        #warning At least version 1800 of Intel C/C++ Compiler (18.0.0) is required for <filesystem> support!
    #endif
#endif