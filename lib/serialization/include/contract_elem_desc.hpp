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
        static constexpr ContractElemDesc CreateScalar();

        static constexpr ContractElemDesc CreateBinary(bool fixed_len, int32_t cont_len);

        template<typename T, 
                    typename = std::enable_if_t<std::is_integral_v<T> 
                    || std::is_floating_point_v<T>>>
        static constexpr ContractElemDesc CreateArray(bool fixed_len, int32_t cont_len);

        // static constexpr ContractElemDesc CreateStringUTF8(bool fixed_len, int32_t cont_len);

        static constexpr ContractElemDesc CreatePackedBoolArray(bool fixed_len, int32_t cont_len);

        template<typename T, typename std::enable_if_t<
            std::is_same_v<std::basic_string<typename T::value_type>, std::decay_t<T>>>>
        static constexpr ContractElemDesc CreateString(bool fixed_len, int32_t cont_len);

    private:

        template<typename T>
        static constexpr ContractElemDesc I_CreateScalar_Integer();

        template<typename T>
        static constexpr ContractElemDesc I_CreateScalar_Float();

        // static constexpr ContractElemDesc I_CreateStringUTF8(bool fixed_len, int32_t cont_len);

        static constexpr ContractElemDesc I_CreateString(bool fixed_len, int32_t cont_len);
        static constexpr ContractElemDesc I_CreateStringUTF16(bool fixed_len, int32_t cont_len);
        static constexpr ContractElemDesc I_CreateStringUTF32(bool fixed_len, int32_t cont_len);    
    };
}

#include "contract_elem_desc.inl"