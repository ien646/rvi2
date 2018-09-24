#include <cinttypes>

namespace rvi::serialization
{
	enum class contract_elem_type : uint8_t
    {
        V_UNDEFINED = 0xFF,

        // -- SCALAR TYPES --
        SCALAR_UINT8  = 0x01,
        SCALAR_UINT16 = 0x02,
        SCALAR_UINT32 = 0x03,
        SCALAR_UINT64 = 0x04,
        SCALAR_INT8   = 0x05,
        SCALAR_INT16  = 0x06,
        SCALAR_INT32  = 0x07,
        SCALAR_INT64  = 0x08,
        
        // -- RAW BINARY TYPES --
        BINARY_FIXLEN = 0x09,
        BINARY_VARLEN = 0x0A,

        // -- ARRAYS --
        ARRAY_SCALAR_VARLEN = 0x10,
        ARRAY_SCALAR_FIXLEN = 0x11,

        // -- UTF8 STRINGS --
        STRING_UTF8_FIXLEN = 0x20,
        STRING_UTF8_VARLEN = 0x21, 

        // -- PACKED BOOL ARRAYS --
        BOOL_ARRAY_VARLEN  = 0x30,
        BOOL_ARRAY_FIXLEN  = 0x31,

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