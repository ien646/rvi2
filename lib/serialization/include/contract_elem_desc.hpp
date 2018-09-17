#include <cinttypes>
#include <type_traits>

#include "contract_elem_type.hpp"

namespace rvi::serialization
{
    class ContractElemDesc
	{    
    public:
        ContractElemType Type   = ContractElemType::V_UNINITIALIZED;
        int32_t ItemSize        = -1;
        int32_t ContainerLen    = -1;
		
        static constexpr int32_t UNDEFINED_SZ = -1;

        ContractElemDesc() = default;
        ContractElemDesc(ContractElemType type);

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

        static ContractElemDesc CreateBinary(bool fixed_len, int32_t cont_len);

        template<typename T>
        static ContractElemDesc CreateArray(bool fixed_len, int32_t cont_len)
        {
            constexpr auto sz = sizeof(T);

            ContractElemDesc result;
            result.ItemSize = sz;
            
            if (fixed_len)
            {
                result.Type = ContractElemType::ARRAY_FIXLEN_ARBITRARY;
                result.ContainerLen = cont_len;
            }
            else
            {
                result.Type = ContractElemType::ARRAY_VARLEN;
                result.ContainerLen = UNDEFINED_SZ;
            }

            return result;
        }

        static ContractElemDesc CreateStringUTF8(bool fixed_len, int32_t cont_len);

        static ContractElemDesc CreatePackedBoolArray(bool fixed_len, int32_t cont_len);

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
    };
}