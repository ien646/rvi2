/* FILE: rvi_base.h */
#pragma once

#include <cstdint>
#include <random>
#include <vector>
#include <unordered_map>
#include <type_traits>

namespace rvi
{
    #define RVI_CONCAT(x,y) x##y
    #define FWD_DECL_CLASS(X) class X

    // Generate a unique prefixed name
    #define RVI_UNIQUENAME(prefix) RVI_CONCAT(prefix,__COUNTER__)

    // Discard return value explicitly
    #define DISCARD_RESULT auto RVI_UNIQUENAME(_trash_) =

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

    // Template helper macros
    #define TEMPLATE_ENABLE_IF_IS_POD(T)		typename = std::enable_if_t<std::is_pod_v<T>>
    #define TEMPLATE_ENABLE_IF_IS_INTEGER(T)	typename = std::enable_if_t<std::is_integral_v<T>>
    #define TEMPLATE_ENABLE_IF_IS_FLOAT(T)		typename = std::enable_if_t<std::is_floating_point_v<T>>
    #define TEMPLATE_ENABLE_IF_IS_STRING(T)		typename = std::enable_if_t<std::is_same_v<std::basic_string<T::value_type>,T>>

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Integer data typedefs
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    using U8  = std::uint8_t;
    using U16 = std::uint16_t;
    using U32 = std::uint32_t;
    using U64 = std::uint64_t;

    using I8  = std::int8_t;
    using I16 = std::int16_t;
    using I32 = std::int32_t;
    using I64 = std::int64_t;
   
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Endianess constant expressions
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    static constexpr U16 _RVI_CEXPR_ENDIAN_MAGIC_NUMBER = 0x00FF;
    static constexpr bool RVI_CEXPR_BIG_ENDIAN      = ((const uint8_t&)_RVI_CEXPR_ENDIAN_MAGIC_NUMBER) == 0x00;
    static constexpr bool RVI_CEXPR_LITTLE_ENDIAN   = ((const uint8_t&)_RVI_CEXPR_ENDIAN_MAGIC_NUMBER) == 0xFF;

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Random integer generator
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
}