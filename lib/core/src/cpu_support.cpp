#include <rvi/cpu_support.hpp>

#if CURRENT_OS_WINDOWS

#include <intrin.h>
#include <iostream>

namespace rvi::cpu_support::x86
{
    std::unordered_map<int, bool> feature_map = {
        { (int)feature::ABM,         false },
        { (int)feature::ADX,         false },
        { (int)feature::AES,         false },
        { (int)feature::AVX2,        false },
        { (int)feature::AVX512BW,    false },
        { (int)feature::AVX512CD,    false },
        { (int)feature::AVX512DQ,    false },
        { (int)feature::AVX512ER,    false },
        { (int)feature::AVX512F,     false },
        { (int)feature::AVX512IFMA,  false },
        { (int)feature::AVX512PF,    false },
        { (int)feature::AVX512VBMI,  false },
        { (int)feature::AVX512VL,    false },
        { (int)feature::AVX,         false },
        { (int)feature::BMI1,        false },
        { (int)feature::BMI2,        false },
        { (int)feature::FMA3,        false },
        { (int)feature::FMA4,        false },
        { (int)feature::MMX,         false },
        { (int)feature::PREFETCHWT1, false },
        { (int)feature::RDRAND,      false },
        { (int)feature::SHA,         false },
        { (int)feature::SSE2,        false },
        { (int)feature::SSE3,        false },
        { (int)feature::SSE41,       false },
        { (int)feature::SSE42,       false },
        { (int)feature::SSE4a,       false },
        { (int)feature::SSE,         false },
        { (int)feature::SSSE3,       false },
        { (int)feature::x64,         false },
        { (int)feature::XOP,         false }
    };    
    
    std::unordered_map<int, std::string> feature_names = {
        { (int)feature::ABM,         "ABM        " },
        { (int)feature::ADX,         "ADX        " },
        { (int)feature::AES,         "AES        " },
        { (int)feature::AVX2,        "AVX2       " },
        { (int)feature::AVX512BW,    "AVX512BW   " },
        { (int)feature::AVX512CD,    "AVX512CD   " },
        { (int)feature::AVX512DQ,    "AVX512DQ   " },
        { (int)feature::AVX512ER,    "AVX512ER   " },
        { (int)feature::AVX512F,     "AVX512F    " },
        { (int)feature::AVX512IFMA,  "AVX512IFMA " },
        { (int)feature::AVX512PF,    "AVX512PF   " },
        { (int)feature::AVX512VBMI,  "AVX512VBMI " },
        { (int)feature::AVX512VL,    "AVX512VL   " },
        { (int)feature::AVX,         "AVX        " },
        { (int)feature::BMI1,        "BMI1       " },
        { (int)feature::BMI2,        "BMI2       " },
        { (int)feature::FMA3,        "FMA3       " },
        { (int)feature::FMA4,        "FMA4       " },
        { (int)feature::MMX,         "MMX        " },
        { (int)feature::PREFETCHWT1, "PREFETCHWT1" },
        { (int)feature::RDRAND,      "RDRAND     " },
        { (int)feature::SHA,         "SHA        " },
        { (int)feature::SSE2,        "SSE2       " },
        { (int)feature::SSE3,        "SSE3       " },
        { (int)feature::SSE41,       "SSE41      " },
        { (int)feature::SSE42,       "SSE42      " },
        { (int)feature::SSE4a,       "SSE4a      " },
        { (int)feature::SSE,         "SSE        " },
        { (int)feature::SSSE3,       "SSSE3      " },
        { (int)feature::x64,         "x64        " },
        { (int)feature::XOP,         "XOP        " }
    };

    void W32_CPUID(int* info, int x)
    { 
        __cpuidex(info, x, 0);
    }

    bool initialized = false;
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
            W32_CPUID(info, 0x00000001);
            feature_map[(int)feature::MMX]    = (info[3] & (1 << 23)) != 0;
            feature_map[(int)feature::SSE]    = (info[3] & (1 << 25)) != 0;
            feature_map[(int)feature::SSE2]   = (info[3] & (1 << 26)) != 0;
            feature_map[(int)feature::SSE3]   = (info[2] & (1 <<  0)) != 0;
            feature_map[(int)feature::SSSE3]  = (info[2] & (1 <<  9)) != 0;
            feature_map[(int)feature::SSE41]  = (info[2] & (1 << 19)) != 0;
            feature_map[(int)feature::SSE42]  = (info[2] & (1 << 20)) != 0;
            feature_map[(int)feature::AES]    = (info[2] & (1 << 25)) != 0;
            feature_map[(int)feature::AVX]    = (info[2] & (1 << 28)) != 0;
            feature_map[(int)feature::FMA3]   = (info[2] & (1 << 12)) != 0;
            feature_map[(int)feature::RDRAND] = (info[2] & (1 << 30)) != 0;
        }
        if (nIds >= 0x00000007)
        {
            W32_CPUID(info,0x00000007);
            feature_map[(int)feature::AVX2]        = (info[1] & (1 <<  5)) != 0;
            feature_map[(int)feature::BMI1]        = (info[1] & (1 <<  3)) != 0;
            feature_map[(int)feature::BMI2]        = (info[1] & (1 <<  8)) != 0;
            feature_map[(int)feature::ADX]         = (info[1] & (1 << 19)) != 0;
            feature_map[(int)feature::SHA]         = (info[1] & (1 << 29)) != 0;
            feature_map[(int)feature::PREFETCHWT1] = (info[2] & (1 <<  0)) != 0;
            feature_map[(int)feature::AVX512F]     = (info[1] & (1 << 16)) != 0;
            feature_map[(int)feature::AVX512CD]    = (info[1] & (1 << 28)) != 0;
            feature_map[(int)feature::AVX512PF]    = (info[1] & (1 << 26)) != 0;
            feature_map[(int)feature::AVX512ER]    = (info[1] & (1 << 27)) != 0;
            feature_map[(int)feature::AVX512VL]    = (info[1] & (1 << 31)) != 0;
            feature_map[(int)feature::AVX512BW]    = (info[1] & (1 << 30)) != 0;
            feature_map[(int)feature::AVX512DQ]    = (info[1] & (1 << 17)) != 0;
            feature_map[(int)feature::AVX512IFMA]  = (info[1] & (1 << 21)) != 0;
            feature_map[(int)feature::AVX512VBMI]  = (info[2] & (1 <<  1)) != 0;
        }
        if (nExIds >= 0x80000001)
        {
            W32_CPUID(info,0x80000001);
            feature_map[(int)feature::x64]   = (info[3] & (1 << 29)) != 0;
            feature_map[(int)feature::ABM]   = (info[2] & (1 <<  5)) != 0;
            feature_map[(int)feature::SSE4a] = (info[2] & (1 <<  6)) != 0;
            feature_map[(int)feature::FMA4]  = (info[2] & (1 << 16)) != 0;
            feature_map[(int)feature::XOP]   = (info[2] & (1 << 11)) != 0;
        }
    }
    
    void print_enabled_features(std::ostream& ostr)
    {
        if(!initialized)
        {
            init();
            initialized = true;
        }

        ostr << "-- Enabled CPU features (x86) --" << std::endl;
        for(auto& [ftype, enabled] : feature_map)
        {            
            ostr << " >> [" << feature_names.at(ftype).c_str() << "] "
                 << (enabled ? "YES" : "NO") << std::endl;
        }
        ostr << std::endl;
    }

    bool get_feature(feature f)
    {
        if(!initialized)
        {
            init();
            initialized = true;
        }
        return feature_map[(int)f];
    }
}

#endif