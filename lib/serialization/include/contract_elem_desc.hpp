#include <cinttypes>
#include <type_traits>
#include <string>

#include "contract_elem_type.hpp"

namespace rvi::serialization
{
    class ContractElemDesc
	{
    public:
        ContractElemType Type   = ContractElemType::V_UNDEFINED;
        int32_t ItemSize        = -1;
        int32_t ContainerLen    = -1;
		
        static constexpr int32_t UNDEFINED_SZ = -1;

        constexpr ContractElemDesc() {};
        constexpr ContractElemDesc(ContractElemType type)
            : Type(type)
        { }

        template<typename T, 
                 typename = std::enable_if_t<std::is_integral_v<T> 
                 || std::is_floating_point_v<T>>>
        static constexpr ContractElemDesc CreateScalar()
        {
            if constexpr(std::is_floating_point_v<T>)
            {
                return Internal_CreateScalar_Float<T>();
            }            
            else
            {
                return Internal_CreateScalar_Integer<T>();
            }
        }

        static constexpr ContractElemDesc CreateBinary(bool fixed_len, int32_t cont_len)
        {
            ContractElemDesc result;		
            result.ContainerLen = cont_len;
            if (fixed_len)
            {
                result.Type = ContractElemType::BINARY_FIXLEN;
            }
            else
            {
                result.Type = ContractElemType::BINARY_VARLEN;
            }
            return result;
        }

        template<typename T>
        static constexpr ContractElemDesc CreateArray(bool fixed_len, int32_t cont_len)
        {
            constexpr auto sz = sizeof(T);

            ContractElemDesc result;
            result.ItemSize = sz;
            
            if (fixed_len)
            {
                result.Type = ContractElemType::ARRAY_SCALAR_FIXLEN;
                result.ContainerLen = cont_len;
            }
            else
            {
                result.Type = ContractElemType::ARRAY_SCALAR_VARLEN;
                result.ContainerLen = UNDEFINED_SZ;
            }
            return result;
        }

        static constexpr ContractElemDesc CreateStringUTF8(bool fixed_len, int32_t cont_len)
        {
            ContractElemDesc result;
            if(fixed_len)
            {
                result.Type = ContractElemType::STRING_UTF8_FIXLEN;
                result.ContainerLen = cont_len;
            }
            else
            {
                result.Type = ContractElemType::STRING_UTF8_VARLEN;
                result.ContainerLen = UNDEFINED_SZ;
            }
            return result;
        }

        static constexpr ContractElemDesc CreatePackedBoolArray(bool fixed_len, int32_t cont_len)
        {
            ContractElemDesc result;
            if(fixed_len)
            {
                result.ContainerLen = cont_len;
                result.Type = ContractElemType::BOOL_ARRAY_FIXLEN;
		    }
            else
            {
                result.ContainerLen = UNDEFINED_SZ;
                result.Type = ContractElemType::BOOL_ARRAY_VARLEN;
            }
		    return result;
        }

        template<typename T, typename std::enable_if_t<
            std::is_same_v<std::basic_string<typename T::value_type>, T>>>
        static constexpr ContractElemDesc CreateString(bool fixed_len, int32_t cont_len)
        {
            if constexpr(std::is_same<typename T::value_type, std::string::value_type>::value)
            {
                return Internal_CreateString(fixed_len, cont_len);
            }
            else if constexpr(std::is_same<typename T::value_type, std::u16string::value_type>::value)
            {
                return Internal_CreateStringUTF16(fixed_len, cont_len);
            }
            else if constexpr(std::is_same<typename T::value_type, std::u32string::value_type>::value)
            {
                return Internal_CreateStringUTF32(fixed_len, cont_len);
            }
            else
            {
                return ContractElemDesc(ContractElemType::V_UNINITIALIZED);
            }
        }

    private:
        template<typename T>
        static constexpr ContractElemDesc Internal_CreateScalar_Integer()
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
            
            ContractElemDesc result;
            result.ItemSize = sizeof(T);
            if constexpr(std::is_signed_v<T>)
            {
                if constexpr(sz == 1)
                    result.Type = ContractElemType::SCALAR_INT8;
                else if constexpr(sz == 2)
                    result.Type = ContractElemType::SCALAR_INT16;
                else if constexpr(sz == 4)
                    result.Type = ContractElemType::SCALAR_INT32;
                else if constexpr(sz == 8)
                    result.Type = ContractElemType::SCALAR_INT64;
            }
            else
            {
                if constexpr(sz == 1)
                    result.Type = ContractElemType::SCALAR_UINT8;
                else if constexpr(sz == 2)
                    result.Type = ContractElemType::SCALAR_UINT16;
                else if constexpr(sz == 4)
                    result.Type = ContractElemType::SCALAR_UINT32;
                else if constexpr(sz == 8)
                    result.Type = ContractElemType::SCALAR_UINT64;
            }
            return result;
        }

        template<typename T>
        static constexpr ContractElemDesc Internal_CreateScalar_Float()
        {
            static_assert(std::is_floating_point_v<T>);
            constexpr auto sz = sizeof(T);

            static_assert(
                sz == 4 ||
                sz == 8,
                "Invalid scalar floating-point size for ContractElemDesc"
            );

            ContractElemDesc result;
            if constexpr(sz == 4)
                result.Type = ContractElemType::SCALAR_FLOAT32;
            else if constexpr(sz == 8)
                result.Type = ContractElemType::SCALAR_FLOAT64;

            return result;
        }

        static constexpr ContractElemDesc Internal_CreateString(bool fixed_len, int32_t cont_len)
        {
            ContractElemDesc result;
            if(fixed_len)
            {
                result.ContainerLen = cont_len;
                result.Type = ContractElemType::STRING_FIXLEN;
            }
            else
            {
                result.ContainerLen = UNDEFINED_SZ;
                result.Type = ContractElemType::STRING_VARLEN;
            }
            return result;
        }

        static constexpr ContractElemDesc Internal_CreateStringUTF16(bool fixed_len, int32_t cont_len)
        {
            ContractElemDesc result;
            if(fixed_len)
            {
                result.ContainerLen = cont_len;
                result.Type = ContractElemType::STRING_UTF16_FIXLEN;
            }
            else
            {
                result.ContainerLen = UNDEFINED_SZ;
                result.Type = ContractElemType::STRING_UTF16_VARLEN;
            }
            return result;
        }

        static constexpr ContractElemDesc Internal_CreateStringUTF32(bool fixed_len, int32_t cont_len)
        {
            ContractElemDesc result;
            if(fixed_len)
            {
                result.ContainerLen = cont_len;
                result.Type = ContractElemType::STRING_UTF32_FIXLEN;
            }
            else
            {
                result.ContainerLen = UNDEFINED_SZ;
                result.Type = ContractElemType::STRING_UTF32_VARLEN;
            }
            return result;
        }
    };
}