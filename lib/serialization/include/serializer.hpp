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
        typedef std::vector<uint8_t> buff_t;

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

        void FillContractBinary_FixLen(const buff_t& val, int contract_iidx);
        void FillContractBinary_VarLen(const buff_t& val, int contract_iidx);

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void FillContractArray_FixLen(const std::vector<T>& val, int contract_iidx)
        {
            const auto cont_len = val.size();
            CheckContractValidType(contract_iidx, ContractElemType::ARRAY_SCALAR_FIXLEN);
            CheckMaxContainerLength(cont_len);

            SerializeArray(_buffer, val);
        }

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void FillContractArray_VarLen(const std::vector<T>& val, int contract_iidx)
        {
            const auto cont_len = val.size();
            CheckContractValidType(contract_iidx, ContractElemType::ARRAY_SCALAR_VARLEN);
            CheckMaxContainerLength(cont_len);
            
            SerializeContainerLen(_buffer, cont_len);
            SerializeArray(_buffer, val);
        }

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
        void I_FillContractIntegral(buff_t& buff, T val, int contract_iidx, ContractElemType type)
        {
            CheckContractValidType(contract_iidx, type);
            SerializeIntegral(buff, val);
        }

        void I_FillContractFloat32(buff_t& buff, float val, int contract_iidx, ContractElemType type);
        void I_FillContractFloat64(buff_t& buff, double val, int contract_iidx, ContractElemType type);

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void SerializeIntegral(buff_t& buff, T val)
        {
            constexpr auto tsz = sizeof(T);
            if constexpr(tsz == sizeof(uint8_t))
            {
                _buffer.push_back(val);
            }
            else
            {
                for(int i = 0; i < tsz; i++)
                {
                    uint8_t byt = static_cast<uint8_t>(val >> (i * 8));
                    _buffer.push_back(byt);
                }
            }
        }

        void SerializeFloat32(buff_t& buff, float val);
        void SerializeFloat64(buff_t& buff, double val);

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void SerializeArray(buff_t& buff, const std::vector<T>& val)
        {
            for (int i = 0; i < cont_len; i++)
            {
                if constexpr (std::is_floating_point_v<T>)
                {
                    SerializeFloat(buff, val[i]);
                }
                else
                {
                    SerializeIntegral(buff, val[i]);
                }
            }
        }

        void SerializeBoolArray(buff_t& buff, const std::vector<bool>& val);

        void SerializeUtf16String(buff_t& buff, const std::u16string& val);

        void SerializeUtf32String(buff_t& buff, const std::u32string& val);

        void SerializeContainerLen(buff_t& buff, size_t cont_len);
    };
}