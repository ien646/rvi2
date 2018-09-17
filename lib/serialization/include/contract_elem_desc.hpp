#include <cinttypes>
#include <type_traits>

#include "contract_elem_type.hpp"

namespace rvi::serialization
{	
    class ContractElemDescriptor
	{
    public:
        ContractElemType Type   = ContractElemType::V_UNINITIALIZED;
        int32_t ItemSize        = -1;
        int32_t ContainerLen    = -1;
        int32_t ArrayFixedLen   = -1;
		
        ContractElemDescriptor() = default;
        ContractElemDescriptor(ContractElemType type);

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        static ContractElemDescriptor CreateScalar()
        {
            ContractElemDescriptor result;

            constexpr size_t sz = sizeof(T);

            static_assert(
                sz == 1 ||
                sz == 2 ||
                sz == 4 ||
                sz == 8,
                "Invalid scalar size for ContractElemDescriptor"
            );

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
    };
}