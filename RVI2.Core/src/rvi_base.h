/* FILE: rviTypes.h */
#pragma once

#include <cstdint>
#include <random>
#include <vector>
#include <unordered_map>
#include <type_traits>

#define CONCAT(x,y) x##y

// Generate a unique prefixed name
#define UNIQUENAME(prefix) CONCAT(prefix,__COUNTER__)

// Discard return value explicitly
#define DISCARD auto UNIQUENAME(____trash_) =

// Compiler conditional macros
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) /* MSVC++ */
	#define RVI_COMPILER_MSVC 1
#elif defined(__GNUC__) || defined(__GNUG__) && !defined(__clang__) /* GNU GCC/G++ */
	#define RVI_COMPILER_GNU 1
#elif defined(__clang__) /* CLANG */
	#define RVI_COMPILER_CLANG 1
#elif defined(__INTEL_COMPILER) || defined(__ICC) /* INTEL C/C++ COMPILER */
	#define RVI_COMPILER_INTEL 1
#endif

namespace rvi
{
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Integer data types
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    typedef std::uint8_t    U8;
    typedef std::uint16_t   U16;
    typedef std::uint32_t   U32;
    typedef std::uint64_t   U64;

    typedef std::int8_t     I8;
    typedef std::int16_t    I16;
    typedef std::int32_t    I32;
    typedef std::int64_t    I64;

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Random generator
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    class Random
    {
    private:
        std::random_device _rnd_dev;

        std::uniform_int_distribution<U64> _distributionU64;
        std::uniform_int_distribution<U32> _distributionU32;
        std::uniform_int_distribution<U16> _distributionU16;

        std::uniform_int_distribution<I64> _distributionI64;
        std::uniform_int_distribution<I32> _distributionI32;
        std::uniform_int_distribution<I16> _distributionI16;

        std::mt19937_64 _mTwisterEngine;
		
    public:
		#if RVI_COMPILER_MSVC
			#pragma warning(suppress: 26439)
		#endif
        Random()
            : _mTwisterEngine(_rnd_dev())
        { }

        U64 GetUnsigned64();
        U32 GetUnsigned32();
        U16 GetUnsigned16();

        I64 GetSigned64();
        I32 GetSigned32();
        I16 GetSigned16();

		static Random DefaultInstance;
    };

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Utilities
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    class Utils
    {
    public:
        template<typename TKey, typename TVal>
        static void GetValuesFromUnorderedMap(std::unordered_map<TKey, TVal> umap, std::vector<TVal&> result)
        {
            for (std::pair<TKey, TVal>& pair : umap)
            {
                result.push_back(pair.second);
            }
        }
    };
}