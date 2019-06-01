#include <rvi/cpu_support.hpp>

#if CURRENT_OS_WINDOWS

#include <intrin.h>
#include <map>
#include <iostream>

void W32_CPUID(int* info, int x)
{ 
    __cpuidex(info, x, 0);
}

namespace rvi::cpu_support::x86
{             
    std::map<feature, bool> feature_map;
    std::map<feature, std::string> feature_names =
    {
        { feature::ABM,         "ABM        " },
        { feature::ADX,         "ADX        " },
        { feature::AES,         "AES        " },
        { feature::AVX2,        "AVX2       " },
        { feature::AVX512BW,    "AVX512BW   " },
        { feature::AVX512CD,    "AVX512CD   " },
        { feature::AVX512DQ,    "AVX512DQ   " },
        { feature::AVX512ER,    "AVX512ER   " },
        { feature::AVX512F,     "AVX512F    " },
        { feature::AVX512IFMA,  "AVX512IFMA " },
        { feature::AVX512PF,    "AVX512PF   " },
        { feature::AVX512VBMI,  "AVX512VBMI " },
        { feature::AVX512VL,    "AVX512VL   " },
        { feature::AVX,         "AVX        " },
        { feature::BMI1,        "BMI1       " },
        { feature::BMI2,        "BMI2       " },
        { feature::FMA3,        "FMA3       " },
        { feature::FMA4,        "FMA4       " },
        { feature::MMX,         "MMX        " },
        { feature::PREFETCHWT1, "PREFETCHWT1" },
        { feature::RDRAND,      "RDRAND     " },
        { feature::SHA,         "SHA        " },
        { feature::SSE2,        "SSE2       " },
        { feature::SSE3,        "SSE3       " },
        { feature::SSE41,       "SSE41      " },
        { feature::SSE42,       "SSE42      " },
        { feature::SSE4a,       "SSE4a      " },
        { feature::SSE,         "SSE        " },
        { feature::SSSE3,       "SSSE3      " },
        { feature::x64,         "x64        " },
        { feature::XOP,         "XOP        " }
    };
    
    bool initialized = false;

    void init();

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
            ostr << " >> [" << feature_names[ftype].c_str() << "] "
                 << (enabled ? "YES" : "NO") << std::endl;
        }
        ostr << std::endl;
    }

    bool get_cpu_feature(feature f)
    {
        if(!initialized)
        {
            init();
            initialized = true;
        }
        return feature_map[f];
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
            feature_map[feature::MMX]    = (info[3] & (1 << 23)) != 0;
            feature_map[feature::SSE]    = (info[3] & (1 << 25)) != 0;
            feature_map[feature::SSE2]   = (info[3] & (1 << 26)) != 0;
            feature_map[feature::SSE3]   = (info[2] & (1 <<  0)) != 0;
            feature_map[feature::SSSE3]  = (info[2] & (1 <<  9)) != 0;
            feature_map[feature::SSE41]  = (info[2] & (1 << 19)) != 0;
            feature_map[feature::SSE42]  = (info[2] & (1 << 20)) != 0;
            feature_map[feature::AES]    = (info[2] & (1 << 25)) != 0;
            feature_map[feature::AVX]    = (info[2] & (1 << 28)) != 0;
            feature_map[feature::FMA3]   = (info[2] & (1 << 12)) != 0;
            feature_map[feature::RDRAND] = (info[2] & (1 << 30)) != 0;
        }
        if (nIds >= 0x00000007)
        {
            W32_CPUID(info,0x00000007);
            feature_map[feature::AVX2]        = (info[1] & (1 <<  5)) != 0;
            feature_map[feature::BMI1]        = (info[1] & (1 <<  3)) != 0;
            feature_map[feature::BMI2]        = (info[1] & (1 <<  8)) != 0;
            feature_map[feature::ADX]         = (info[1] & (1 << 19)) != 0;
            feature_map[feature::SHA]         = (info[1] & (1 << 29)) != 0;
            feature_map[feature::PREFETCHWT1] = (info[2] & (1 <<  0)) != 0;
            feature_map[feature::AVX512F]     = (info[1] & (1 << 16)) != 0;
            feature_map[feature::AVX512CD]    = (info[1] & (1 << 28)) != 0;
            feature_map[feature::AVX512PF]    = (info[1] & (1 << 26)) != 0;
            feature_map[feature::AVX512ER]    = (info[1] & (1 << 27)) != 0;
            feature_map[feature::AVX512VL]    = (info[1] & (1 << 31)) != 0;
            feature_map[feature::AVX512BW]    = (info[1] & (1 << 30)) != 0;
            feature_map[feature::AVX512DQ]    = (info[1] & (1 << 17)) != 0;
            feature_map[feature::AVX512IFMA]  = (info[1] & (1 << 21)) != 0;
            feature_map[feature::AVX512VBMI]  = (info[2] & (1 <<  1)) != 0;
        }
        if (nExIds >= 0x80000001)
        {
            W32_CPUID(info,0x80000001);
            feature_map[feature::x64]   = (info[3] & (1 << 29)) != 0;
            feature_map[feature::ABM]   = (info[2] & (1 <<  5)) != 0;
            feature_map[feature::SSE4a] = (info[2] & (1 <<  6)) != 0;
            feature_map[feature::FMA4]  = (info[2] & (1 << 16)) != 0;
            feature_map[feature::XOP]   = (info[2] & (1 << 11)) != 0;
        }
    }
}

#endif