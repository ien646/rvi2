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

        void FillContractScalarU8(uint8_t val, int elemidx);
        void FillContractScalarU16(uint16_t val, int elemidx);
        void FillContractScalarU32(uint32_t val, int elemidx);
        void FillContractScalarU64(uint64_t val, int elemidx);
        void FillContractScalarI8(int8_t val, int elemidx);
        void FillContractScalarI16(int16_t val, int elemidx);
        void FillContractScalarI32(int32_t val, int elemidx);
        void FillContractScalarI64(int64_t val, int elemidx);

        void FillContractScalarFP32(float val, int elemidx);
        void FillContractScalarFP64(double val, int elemidx);

        void FillContractBinary_FixLen(const std::vector<uint8_t>& val, int elemidx);
        void FillContractBinary_VarLen(const std::vector<uint8_t>& val, int elemidx);

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void FillContractElemArray_FixLen(std::vector<T>& val, int elemidx)
        {
            const auto cont_len = val.size();
            CheckContractValidType(elemidx, ContractElemType::ARRAY_SCALAR_FIXLEN);
            CheckMaxContainerLength(cont_len);
            Internal_SerializeArray(_buffer, val);
        }

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void FillContractElemArray_VarLen(std::vector<T>& val, int elemidx)
        {
            const auto cont_len = val.size();
            CheckContractValidType(elemidx, ContractElemType::ARRAY_SCALAR_VARLEN);
            CheckMaxContainerLength(cont_len);
            
            uint16_t fxsz = static_cast<uint16_t>(cont_len);
            Internal_SerializeIntegral(_buffer, fxsz);

            Internal_SerializeArray(_buffer, val);
        }

    private:
        void CheckContractValidFixedSize(int elemidx, int cont_len);
        void CheckContractValidVarSize(int elemidx, int cont_len);
        void CheckContractValidType(int elemidx, ContractElemType type);
        void CheckMaxContainerLength(size_t cont_len);

        void Throw_InvalidTypeForContract(const ContractElemDesc& descriptor);
        void Throw_FixedSizeItemLengthOverflow(const ContractElemDesc& descriptor, int cont_sz);
        void Throw_VarSizeItemLengthOverflow(const ContractElemDesc& descriptor, int cont_sz);        

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void Internal_FillContractElemIntegral(std::vector<uint8_t>& buff, T val, int elemidx, ContractElemType type)
        {
            CheckContractValidType(elemidx, type);
            Internal_SerializeIntegral(buff, val);
        }

        template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
        void Internal_FillContractElemFloat(std::vector<uint8_t>& buff, T val, int elemidx, ContractElemType type)
        {
            CheckContractValidType(elemidx, type);
            Internal_SerializeFloat(buff, val);
        }

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void Internal_SerializeIntegral(std::vector<uint8_t>& buff, T val)
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

        template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
        void Internal_SerializeFloat(std::vector<uint8_t>& buff, T val)
        {
            constexpr auto tsz = sizeof(T);
            if constexpr(tsz == sizeof(float))
            {
                uint32_t* ptr = reinterpret_cast<uint32_t*>(&val);
                for(int i = 0; i < tsz; i++)
                {
                    uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
                    _buffer.push_back(byt);
                }
            }
            else if constexpr(tsz == sizeof(double))
            {
                uint64_t* ptr = reinterpret_cast<uint64_t*>(&val);
                for(int i = 0; i < tsz; i++)
                {
                    uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
                    _buffer.push_back(byt);
                }
            }
        }

        template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
        void Internal_SerializeArray(std::vector<uint8_t>& buff, std::vector<T>& val)
        {
            for (int i = 0; i < cont_len; i++)
            {
                if constexpr (std::is_floating_point_v<T>)
                {
                    Internal_SerializeFloat(buff, val[i]);
                }
                else
                {
                    Internal_SerializeIntegral(buff, val[i]);
                }
            }
        }
    };
}