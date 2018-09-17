#include "serializer.hpp"

namespace rvi::serialization
{
    void Serializer::FillContractScalarU8(uint8_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_UINT8);
    }

    void Serializer::FillContractScalarU16(uint16_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_UINT16);
    }

    void Serializer::FillContractScalarU32(uint32_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_UINT32);
    }

    void Serializer::FillContractScalarU64(uint64_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_UINT64);
    }

    void Serializer::FillContractScalarI8(int8_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_INT8);
    }

    void Serializer::FillContractScalarI16(int16_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_INT16);
    }

    void Serializer::FillContractScalarI32(int32_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_INT32);
    }

    void Serializer::FillContractScalarI64(int64_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(_buffer, val, elemidx, ContractElemType::SCALAR_INT64);
    }

    void Serializer::FillContractScalarFP32(float val, int elemidx)
    {
        Internal_FillContractElemFloat32(_buffer, val, elemidx, ContractElemType::SCALAR_FLOAT32);
    }

    void Serializer::FillContractScalarFP64(double val, int elemidx)
    {
        Internal_FillContractElemFloat64(_buffer, val, elemidx, ContractElemType::SCALAR_FLOAT64);
    }

    void Serializer::FillContractBinary_FixLen(const std::vector<uint8_t>& val, int elemidx)
    {
        CheckContractValidType(elemidx, ContractElemType::BINARY_FIXLEN);
        CheckContractValidFixedSize(elemidx, val.size());

        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void Serializer::FillContractBinary_VarLen(const std::vector<uint8_t>& val, int elemidx)
    {
        CheckContractValidType(elemidx, ContractElemType::BINARY_FIXLEN);
        CheckMaxContainerLength(val.size());

        uint16_t size = static_cast<uint16_t>(val.size());
        Internal_SerializeIntegral(_buffer, size);

        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void Serializer::FillContractElemBoolArray_FixLen(const std::vector<bool>& val, int contract_iidx)
    {
        CheckContractValidType(contract_iidx, ContractElemType::BOOL_ARRAY_FIXLEN);
        CheckMaxContainerLength(val.size());
        CheckContractValidFixedSize(contract_iidx, val.size() / sizeof(uint8_t));

        Internal_SerializeBoolArray(_buffer, val);
    }

    void Serializer::FillContractElemBoolArray_VarLen(const std::vector<bool>& val, int contract_iidx)
    {
        CheckContractValidType(contract_iidx, ContractElemType::BOOL_ARRAY_FIXLEN);
        CheckMaxContainerLength(val.size());

        uint16_t len = static_cast<uint16_t>(val.size());
        Internal_SerializeIntegral<uint16_t>(_buffer, len);

        Internal_SerializeBoolArray(_buffer, val);
    }

    void Serializer::Internal_SerializeFloat32(std::vector<uint8_t>& buff, float val)
    {
        constexpr auto tsz = sizeof(val);
        
        uint32_t* ptr = reinterpret_cast<uint32_t*>(&val);
        for(int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            _buffer.push_back(byt);
        }            
    }

    void Serializer::Internal_FillContractElemFloat32(std::vector<uint8_t>& buff, float val, int contract_elemidx, ContractElemType type)
    {
        CheckContractValidType(contract_elemidx, type);
        Internal_SerializeFloat32(buff, val);
    }

    void Serializer::Internal_SerializeFloat64(std::vector<uint8_t>& buff, double val)
    {
        constexpr auto tsz = sizeof(val);
        
        uint64_t* ptr = reinterpret_cast<uint64_t*>(&val);
        for(int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            _buffer.push_back(byt);
        }            
    }

    void Serializer::Internal_FillContractElemFloat64(std::vector<uint8_t>& buff, double val, int contract_elemidx, ContractElemType type)
    {
        CheckContractValidType(contract_elemidx, type);
        Internal_SerializeFloat64(buff, val);
    }

    void Serializer::CheckContractValidFixedSize(int elemidx, int cont_len)
    {
        const ContractElemDesc& desc = _contract.GetElements().at(elemidx);
        if(cont_len > desc.ContainerLen)
        {
            Throw_FixedSizeItemLengthOverflow(desc, cont_len);
        }
    }  

    void Serializer::CheckMaxContainerLength(size_t cont_len)
    {
        if(cont_len > std::numeric_limits<uint16_t>::max())
        {
            std::stringstream ss;
            ss  << "Invalid container length. Maximum container length: "
                << std::numeric_limits<uint16_t>::max()
                << ", given length: "
                << cont_len
                << std::endl;
            throw std::logic_error(ss.str());
        }
    }

    void Serializer::CheckContractValidType(int elemidx, ContractElemType type)
    {
        const ContractElemDesc& desc = _contract.GetElements().at(elemidx);
        if(type != desc.Type)
        {
            Throw_InvalidTypeForContract(desc);
        }
    }

    void Serializer::Throw_InvalidTypeForContract(const ContractElemDesc& descriptor)
    {
        std::stringstream ss;
        ss  << "Invalid type for contract. Expected:"
            << static_cast<uint8_t>(descriptor.Type)
            << std::endl;
        throw std::logic_error(ss.str());
    }

    void Serializer::Throw_FixedSizeItemLengthOverflow(const ContractElemDesc& descriptor, int cont_sz)
    {
        std::stringstream ss;
        ss << "Invalid container length for fixed size descriptor. Expected (maximum) size: "
            << descriptor.ContainerLen
            << ", given container size: "
            << cont_sz
            << std::endl;
        throw std::logic_error(ss.str());
    }

    void Serializer::Throw_VarSizeItemLengthOverflow(int cont_sz)
    {
        std::stringstream ss;
        ss << "Invalid container length for var size descriptor. Expected (maximum) size: "
            << MAX_CONTAINER_LENGTH
            << ", given size: "
            << cont_sz
            << std::endl;
        throw std::logic_error(ss.str());
    }
}