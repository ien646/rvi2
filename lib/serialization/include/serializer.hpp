#include <cinttypes>
#include <vector>
#include <type_traits>
#include <sstream>
#include <limits>

#include "base.hpp"
#include "contract.hpp"

namespace rvi::serialization
{
    class Serializer
    {
    private:
        std::vector<uint8_t> _buffer;
    	Contract _contract;

        const uint32_t MAX_CONTAINER_LENGTH = 
            static_cast<uint32_t>(std::numeric_limits<uint16_t>::max());

    public:
        Serializer(const Contract& contract)
            : _contract(contract)
        { }

        Serializer(Contract&& contract)
            : _contract(std::move(contract))
        { }

        void FillContractScalarU8(uint8_t val, int contract_iidx);
        void FillContractScalarU16(uint16_t val, int contract_iidx);
        void FillContractScalarU32(uint32_t val, int contract_iidx);
        void FillContractScalarU64(uint64_t val, int contract_iidx);
        void FillContractScalarI8(int8_t val, int contract_iidx);
        void FillContractScalarI16(int16_t val, int contract_iidx);
        void FillContractScalarI32(int32_t val, int contract_iidx);
        void FillContractScalarI64(int64_t val, int contract_iidx);

        void FillContractScalarFP32(float val, int contract_iidx);
        void FillContractScalarFP64(double val, int contract_iidx);

        void FillContractBinary_FixLen(const std::vector<uint8_t>& val, int contract_iidx);
        void FillContractBinary_VarLen(const std::vector<uint8_t>& val, int contract_iidx);

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void FillContractArray_FixLen(const std::vector<T>& val, int contract_iidx);

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void FillContractArray_VarLen(const std::vector<T>& val, int contract_iidx);

        // void FillContractElemUtf8String_FixLen(Utf8String val, int contract_iidx);
        // void FillContractElemUtf8String_VarLen(Utf8String val, int contract_iidx);

        void FillContractBoolArray_FixLen(const std::vector<bool>& val, int contract_iidx);
        void FillContractBoolArray_VarLen(const std::vector<bool>& val, int contract_iidx);

        void FillContractString_FixLen(const std::string& val, int contract_iidx);
        void FillContractString_VarLen(const std::string& val, int contract_iidx);

        void FillContractStringUtf16_FixLen(const std::u16string& val, int contract_iidx);
        void FillContractStringUtf16_VarLen(const std::u16string& val, int contract_iidx);

        void FillContractStringUtf32_FixLen(const std::u32string& val, int contract_iidx);
        void FillContractStringUtf32_VarLen(const std::u32string& val, int contract_iidx);

    private:
        void CheckContractValidFixedSize(int contract_iidx, int cont_len);
        void CheckContractValidVarSize(int cont_len);
        void CheckContractValidType(int contract_iidx, ContractElemType type);
        void CheckMaxContainerLength(size_t cont_len);

        void Throw_InvalidTypeForContract(const ContractElemDesc& descriptor);
        void Throw_FixedSizeItemLengthOverflow(const ContractElemDesc& descriptor, int cont_sz);
        void Throw_VarSizeItemLengthOverflow(int cont_sz);        

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void I_FillContractIntegral(std::vector<uint8_t>& buff, T val, int contract_iidx, ContractElemType type);

        void I_FillContractFloat32(std::vector<uint8_t>& buff, float val, int contract_iidx, ContractElemType type);
        void I_FillContractFloat64(std::vector<uint8_t>& buff, double val, int contract_iidx, ContractElemType type);

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void SerializeIntegral(std::vector<uint8_t>& buff, T val);

        void SerializeFloat32(std::vector<uint8_t>& buff, float val);
        void SerializeFloat64(std::vector<uint8_t>& buff, double val);

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void SerializeArray(std::vector<uint8_t>& buff, const std::vector<T>& val);

        void SerializeBoolArray(std::vector<uint8_t>& buff, const std::vector<bool>& val);
        void SerializeUtf16String(std::vector<uint8_t>& buff, const std::u16string& val);
        void SerializeUtf32String(std::vector<uint8_t>& buff, const std::u32string& val);
        void SerializeContainerLen(std::vector<uint8_t>& buff, size_t cont_len);
    };
}

#include "serializer.inl"
