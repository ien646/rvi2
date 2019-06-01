#pragma once

/*--------------------------------
    ARCHITECTURE 
--------------------------------*/

#if defined(_M_IX86) || defined(_X86_) || defined(__i386__)
    #define CURRENT_ARCH_X86_32 1
#elif defined(_M_AMD64) || defined(__amd64__) || defined(__x86_64__)
    #define CURRENT_ARCH_X86_64 1
#elif defined(__arm__) || defined(_M_ARM)
    #define CURRENT_ARCH_ARM32 1
#elif defined(__aarch64__)
    #define CURRENT_ARCH_ARM64 1
#else
    #define CURRENT_ARCH_UNKNOWN 1
#endif

/*--------------------------------
    OS
--------------------------------*/

#if defined(_WIN32)
    #define CURRENT_OS_WINDOWS 1
#elif defined(__linux__)
    #define CURRENT_OS_LINUX 1
#elif defined(__APPLE__)
    #define CURRENT_OS_MAC
#else 
    #define CURRENT_OS_UNKNOWN
#endif

#if CURRENT_ARCH_X86_32 || CURRENT_ARCH_X86_64
    #include <iostream>    
    namespace rvi::cpu_support::x86
    {
        enum class feature
        {
            ABM, ADX,
            AES, AVX2,
            AVX512BW, AVX512CD,
            AVX512DQ, AVX512ER,
            AVX512F, AVX512IFMA,
            AVX512PF, AVX512VBMI,
            AVX512VL, AVX,
            BMI1, BMI2,
            FMA3, FMA4,
            MMX, PREFETCHWT1,
            RDRAND, SHA,
            SSE2, SSE3,
            SSE41, SSE42,
            SSE4a, SSE,   
            SSSE3, x64,
            XOP
        };

        extern bool get_feature(feature);
        extern void print_enabled_features(std::ostream& = std::cout);
    }
#endif