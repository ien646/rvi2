#include <cinttypes>
#include <type_traits>
#include <string>

#include "contract_elem_type.hpp"
#include "template_helpers.hpp"

namespace rvi::serialization
{
    class contract_elem_desc
	{
    public:
        contract_elem_type type   = contract_elem_type::V_UNDEFINED;
        int32_t item_size        = -1;
        int32_t container_len    = -1;
		
        static constexpr int32_t UNDEFINED_SZ = -1;

        constexpr contract_elem_desc() {};
        constexpr contract_elem_desc(contract_elem_type type)
            : type(type)
        { }

        template<typename T, typename = enable_if_float_or_integral<T>>
        static constexpr contract_elem_desc create_scalar();

        static constexpr contract_elem_desc create_binary(bool fixed_len, int32_t cont_len);

        template<typename T, typename = enable_if_float_or_integral<T>>
        static constexpr contract_elem_desc create_array(bool fixed_len, int32_t cont_len);

        static constexpr contract_elem_desc create_packed_bool_array(bool fixed_len, int32_t cont_len);

        template<typename T, typename = enable_if_std_xstring<T>>
        static constexpr contract_elem_desc create_string(bool fixed_len, int32_t cont_len);

    private:

        template<typename T>
        static constexpr contract_elem_desc i_create_scalar_integer();

        template<typename T>
        static constexpr contract_elem_desc i_create_scalar_float();

        static constexpr contract_elem_desc i_create_string(bool fixed_len, int32_t cont_len);
        static constexpr contract_elem_desc i_create_string_utf16(bool fixed_len, int32_t cont_len);
        static constexpr contract_elem_desc i_create_string_utf32(bool fixed_len, int32_t cont_len);
    };

///////////////////////////////////////////////////////////////////////
// INLINE/TEMPLATE DEFINITIONS
///////////////////////////////////////////////////////////////////////

    template<typename T, typename>
    constexpr contract_elem_desc contract_elem_desc::create_scalar()
    {
        if constexpr(std::is_integral_v<T>)
        {
            return i_create_scalar_integer<T>();
        }
        else
        {
            return i_create_scalar_float<T>();
        }
    }

    constexpr contract_elem_desc contract_elem_desc::create_binary(bool fixed_len, int32_t cont_len)
    {
        contract_elem_desc result;
        if(fixed_len)
        {
            result.container_len = cont_len;
            result.type = contract_elem_type::BINARY_FIXLEN;
        }
        else
        {
            result.container_len= contract_elem_desc::UNDEFINED_SZ; 
            result.type = contract_elem_type::BINARY_VARLEN;
        }
        return result;
    }

    template<typename T, typename>
    constexpr contract_elem_desc contract_elem_desc::create_array(bool fixed_len, int32_t cont_len)
    {
        contract_elem_desc result;
        constexpr auto sz = static_cast<int32_t>(sizeof(T));
        result.item_size = sz;

        if(fixed_len)
        {
            result.container_len = cont_len;
            result.type = contract_elem_type::ARRAY_SCALAR_FIXLEN;
        }
        else
        {
            result.container_len = contract_elem_desc::UNDEFINED_SZ;
            result.type = contract_elem_type::ARRAY_SCALAR_VARLEN;
        }        
        return result;
    }

    constexpr contract_elem_desc contract_elem_desc::create_packed_bool_array(bool fixed_len, int32_t cont_len)
    {
        contract_elem_desc result;
        if(fixed_len)
        {
            result.container_len = cont_len;
            result.type = contract_elem_type::BOOL_ARRAY_FIXLEN;
        }
        else
        {
            result.container_len = contract_elem_desc::UNDEFINED_SZ;
            result.type = contract_elem_type::BOOL_ARRAY_VARLEN;
        }
        return result;
    }

    template<typename T, typename>
    constexpr contract_elem_desc contract_elem_desc::create_string(bool fixed_len, int32_t cont_len)
    {
        if constexpr(std::is_same_v<std::string::value_type, T::value_type>)
        {
            i_create_string(fixed_len, cont_len);
        }
        else if constexpr(std::is_same_v<std::u16string::value_type, T::value_type>)
        {
            i_create_string_utf16(fixed_len, cont_len);
        }
        else if constexpr(std::is_same_v<std::u32string::value_type, T::value_type>)
        {
            i_create_string_utf32(fixed_len, cont_len);
        }
        else
        {
            static_assert(0, "Unknown string character size/type");
        }
    }

    constexpr contract_elem_desc contract_elem_desc::i_create_string_utf32(bool fixed_len, int32_t cont_len)
    {
        contract_elem_desc result;
        if(fixed_len)
        {
            result.container_len = cont_len;
            result.type = contract_elem_type::STRING_UTF32_FIXLEN;
        }
        else
        {
            result.container_len = contract_elem_desc::UNDEFINED_SZ;
            result.type = contract_elem_type::STRING_UTF32_VARLEN;
        }
        return result;
    }        

    constexpr contract_elem_desc contract_elem_desc::i_create_string_utf16(bool fixed_len, int32_t cont_len)
    {
        contract_elem_desc result;
        if(fixed_len)
        {
            result.container_len = cont_len;
            result.type = contract_elem_type::STRING_UTF16_FIXLEN;
        }
        else
        {
            result.container_len = contract_elem_desc::UNDEFINED_SZ;
            result.type = contract_elem_type::STRING_UTF16_VARLEN;
        }
        return result;
    }

    constexpr contract_elem_desc contract_elem_desc::i_create_string(bool fixed_len, int32_t cont_len)
    {
        contract_elem_desc result;
        if(fixed_len)
        {
            result.container_len = cont_len;
            result.type = contract_elem_type::STRING_FIXLEN;
        }
        else
        {
            result.container_len = contract_elem_desc::UNDEFINED_SZ;
            result.type = contract_elem_type::STRING_VARLEN;
        }
        return result;
    }

    template<typename T>
    constexpr contract_elem_desc contract_elem_desc::i_create_scalar_float()
    {
        constexpr auto sz = sizeof(T);

        static_assert(
            sz == 4 ||
            sz == 8,
            "Invalid scalar floating-point size for ContractElemDesc"
        );

        contract_elem_desc result;
        if constexpr(sz == 4)
            result.type = contract_elem_type::SCALAR_FLOAT32;
        else if constexpr(sz == 8)
            result.type = contract_elem_type::SCALAR_FLOAT64;

        return result;
    }

    template<typename T>
    constexpr contract_elem_desc contract_elem_desc::i_create_scalar_integer()
    {
        static_assert(std::is_integral_v<T>, "Type is not integral");
        constexpr auto sz = sizeof(T);

        static_assert(
            sz == 1 ||
            sz == 2 ||
            sz == 4 ||
            sz == 8,
            "Invalid scalar integer size for ContractElemDesc"
        );
        
        contract_elem_desc result;
        result.item_size = sizeof(T);
        if constexpr(std::is_signed_v<T>)
        {
            if constexpr(sz == 1)
                result.type = contract_elem_type::SCALAR_INT8;
            else if constexpr(sz == 2)
                result.type = contract_elem_type::SCALAR_INT16;
            else if constexpr(sz == 4)
                result.type = contract_elem_type::SCALAR_INT32;
            else if constexpr(sz == 8)
                result.type = contract_elem_type::SCALAR_INT64;
        }
        else
        {
            if constexpr(sz == 1)
                result.type = contract_elem_type::SCALAR_UINT8;
            else if constexpr(sz == 2)
                result.type = contract_elem_type::SCALAR_UINT16;
            else if constexpr(sz == 4)
                result.type = contract_elem_type::SCALAR_UINT32;
            else if constexpr(sz == 8)
                result.type = contract_elem_type::SCALAR_UINT64;
        }
        return result;
    }
}