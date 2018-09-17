#include <cinttypes>

namespace rvi::serialization
{
	enum class ContractElemType : uint8_t
    {
        // -- UNINITIALIZED --
        V_UNINITIALIZED = 0xFF,

        // -- SCALAR TYPES --
        SCALAR_UINT8  = 0x00,
        SCALAR_UINT16 = 0x01,
        SCALAR_UINT32 = 0x02,
        SCALAR_UINT64 = 0x03,
        SCALAR_INT8   = 0x04,
        SCALAR_INT16  = 0x05,
        SCALAR_INT32  = 0x06,
        SCALAR_INT64  = 0x07,
        
        // -- RAW BINARY TYPES --
        BINARY_FIXLEN = 0x08,
        BINARY_VARLEN = 0x09,

        // -- ARRAYS --
        ARRAY_VARLEN = 0x10,
        ARRAY_FIXLEN_ARBITRARY = 0x11,
        ARRAY_FIXLEN_2 = 0x12,
        ARRAY_FIXLEN_4 = 0x13,
        ARRAY_FIXLEN_8 = 0x14,
        ARRAY_FIXLEN_16 = 0x15,
        ARRAY_FIXLEN_32 = 0x16,
        ARRAY_FIXLEN_64 = 0x17,

        // -- UTF8 STRINGS --
        STRING_UTF8 = 0x20,

        // -- PACKED BOOL ARRAYS --
        BOOL_ARRAY_PACKED_VARLEN  = 0x30,
        BOOL_ARRAY_PACKED_16 = 0x31,
        BOOL_ARRAY_PACKED_32 = 0x32,
        BOOL_ARRAY_PACKED_64 = 0x33,

        // -- FLOATING POINT --
        SCALAR_FLOAT32 = 0x40,
        SCALAR_FLOAT64 = 0x41,
		
		// -- FIXED CHAR LENGTH STRINGS --
        STRING_VARLEN = 0x50,
        STRING_FIXLEN = 0x51,
		STRING_UTF16_VARLEN = 0x52,
        STRING_UTF16_FIXLEN = 0x53,
		STRING_UTF32_VARLEN = 0x54,
        STRING_UTF32_FIXLEN = 0x55
    };
}