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

#if defined(_WIN32)
    #define CURRENT_OS_WINDOWS 1
#elif defined(__linux__)
    #define CURRENT_OS_LINUX 1
#elif defined(__APPLE__)
    #define CURRENT_OS_MAC
#else 
    #define CURRENT_OS_UNKNOWN
#endif

#if CURRENT_OS_WINDOWS

#include <intrin.h>
#define W32_CPUID(info, x) __cpuidex(info, x, 0)

namespace cpu_support
{
    namespace x86
    {
        bool x64;
        bool ABM;
        bool RDRAND;
        bool BMI1;
        bool BMI2;
        bool ADX;
        bool PREFETCHWT1;

        bool MMX;
        bool SSE;
        bool SSE2;
        bool SSE3;
        bool SSSE3;
        bool SSE41;
        bool SSE42;
        bool SSE4a;
        bool AVX;
        bool AVX2;
        bool AVX512F;
        bool AVX512CD;
        bool AVX512PF;
        bool AVX512ER;
        bool AVX512VL;
        bool AVX512BW;
        bool AVX512DQ;
        bool AVX512IFMA;
        bool AVX512VBMI;

        bool FMA3;
        bool FMA4;

        bool AES;
        bool SHA;
        
        bool XOP;
    }

    void init()
    {        
        int info[4];
        W32_CPUID(info, 0);
        int nIds = info[0];

        W32_CPUID(info, 0x80000000);
        unsigned nExIds = info[0];

        //  Detect Features
        if (nIds >= 0x00000001)
        {
            W32_CPUID(info,0x00000001);
            x86::MMX    = (info[3] & ((int)1 << 23)) != 0;
            x86::SSE    = (info[3] & ((int)1 << 25)) != 0;
            x86::SSE2   = (info[3] & ((int)1 << 26)) != 0;
            x86::SSE3   = (info[2] & ((int)1 <<  0)) != 0;

            x86::SSSE3  = (info[2] & ((int)1 <<  9)) != 0;
            x86::SSE41  = (info[2] & ((int)1 << 19)) != 0;
            x86::SSE42  = (info[2] & ((int)1 << 20)) != 0;
            x86::AES    = (info[2] & ((int)1 << 25)) != 0;

            x86::AVX    = (info[2] & ((int)1 << 28)) != 0;
            x86::FMA3   = (info[2] & ((int)1 << 12)) != 0;

            x86::RDRAND = (info[2] & ((int)1 << 30)) != 0;
        }
        if (nIds >= 0x00000007)
        {
            W32_CPUID(info,0x00000007);
            x86::AVX2   = (info[1] & ((int)1 <<  5)) != 0;

            x86::BMI1        = (info[1] & ((int)1 <<  3)) != 0;
            x86::BMI2        = (info[1] & ((int)1 <<  8)) != 0;
            x86::ADX         = (info[1] & ((int)1 << 19)) != 0;
            x86::SHA         = (info[1] & ((int)1 << 29)) != 0;
            x86::PREFETCHWT1 = (info[2] & ((int)1 <<  0)) != 0;

            x86::AVX512F     = (info[1] & ((int)1 << 16)) != 0;
            x86::AVX512CD    = (info[1] & ((int)1 << 28)) != 0;
            x86::AVX512PF    = (info[1] & ((int)1 << 26)) != 0;
            x86::AVX512ER    = (info[1] & ((int)1 << 27)) != 0;
            x86::AVX512VL    = (info[1] & ((int)1 << 31)) != 0;
            x86::AVX512BW    = (info[1] & ((int)1 << 30)) != 0;
            x86::AVX512DQ    = (info[1] & ((int)1 << 17)) != 0;
            x86::AVX512IFMA  = (info[1] & ((int)1 << 21)) != 0;
            x86::AVX512VBMI  = (info[2] & ((int)1 <<  1)) != 0;
        }
        if (nExIds >= 0x80000001)
        {
            W32_CPUID(info,0x80000001);
            x86::x64   = (info[3] & ((int)1 << 29)) != 0;
            x86::ABM   = (info[2] & ((int)1 <<  5)) != 0;
            x86::SSE4a = (info[2] & ((int)1 <<  6)) != 0;
            x86::FMA4  = (info[2] & ((int)1 << 16)) != 0;
            x86::XOP   = (info[2] & ((int)1 << 11)) != 0;
        }
    }
}

#endif