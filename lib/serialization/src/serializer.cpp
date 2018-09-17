#include "serializer.hpp"

namespace rvi::serialization
{
    void Serializer::FillContractScalarU8(uint8_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_UINT8);
    }

    void Serializer::FillContractScalarU16(uint16_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_UINT16);
    }

    void Serializer::FillContractScalarU32(uint32_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_UINT32);
    }

    void Serializer::FillContractScalarU64(uint64_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_UINT64);
    }

    void Serializer::FillContractScalarI8(int8_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_INT8);
    }

    void Serializer::FillContractScalarI16(int16_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_INT16);
    }

    void Serializer::FillContractScalarI32(int32_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_INT32);
    }

    void Serializer::FillContractScalarI64(int64_t val, int contract_iidx)
    {
        Internal_FillContractIntegral(_buffer, val, contract_iidx, ContractElemType::SCALAR_INT64);
    }

    void Serializer::FillContractScalarFP32(float val, int contract_iidx)
    {
        Internal_FillContractFloat32(_buffer, val, contract_iidx, ContractElemType::SCALAR_FLOAT32);
    }

    void Serializer::FillContractScalarFP64(double val, int contract_iidx)
    {
        Internal_FillContractFloat64(_buffer, val, contract_iidx, ContractElemType::SCALAR_FLOAT64);
    }

    void Serializer::FillContractBinary_FixLen(const std::vector<uint8_t>& val, int contract_iidx)
    {
        CheckContractValidType(contract_iidx, ContractElemType::BINARY_FIXLEN);
        CheckContractValidFixedSize(contract_iidx, val.size());

        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void Serializer::FillContractBinary_VarLen(const std::vector<uint8_t>& val, int contract_iidx)
    {
        CheckContractValidType(contract_iidx, ContractElemType::BINARY_VARLEN);
        CheckMaxContainerLength(val.size());

        SerializeContainerLen(_buffer, val.size());
        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void Serializer::FillContractBoolArray_FixLen(const std::vector<bool>& val, int contract_iidx)
    {
        CheckContractValidType(contract_iidx, ContractElemType::BOOL_ARRAY_FIXLEN);
        CheckMaxContainerLength(val.size());
        CheckContractValidFixedSize(contract_iidx, val.size() / sizeof(uint8_t));

        SerializeBoolArray(_buffer, val);
    }

    void Serializer::FillContractBoolArray_VarLen(const std::vector<bool>& val, int contract_iidx)
    {
        CheckContractValidType(contract_iidx, ContractElemType::BOOL_ARRAY_VARLEN);
        CheckMaxContainerLength(val.size());

        SerializeContainerLen(_buffer, val.size());
        SerializeBoolArray(_buffer, val);
    }

    void Serializer::FillContractString_FixLen(const std::string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::STRING_FIXLEN);
        CheckContractValidFixedSize(contract_iidx, strsz);
        CheckMaxContainerLength(strsz);

        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void Serializer::FillContractString_VarLen(const std::string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::STRING_VARLEN);
        CheckMaxContainerLength(strsz);

        SerializeContainerLen(_buffer, strsz);
        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void Serializer::FillContractStringUtf16_FixLen(const std::u16string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::STRING_UTF16_FIXLEN);
        CheckContractValidFixedSize(contract_iidx, strsz);
        CheckMaxContainerLength(strsz);

        SerializeUtf16String(_buffer, val);
    }

    void Serializer::FillContractStringUtf16_VarLen(const std::u16string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::STRING_UTF16_VARLEN);
        CheckMaxContainerLength(strsz);

        SerializeContainerLen(_buffer, strsz);
        SerializeUtf16String(_buffer, val);
    }

    void Serializer::FillContractStringUtf32_FixLen(const std::u32string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::STRING_UTF32_FIXLEN);
        CheckContractValidFixedSize(contract_iidx, strsz);
        CheckMaxContainerLength(strsz);

        SerializeUtf32String(_buffer, val);
    }

    void Serializer::FillContractStringUtf32_VarLen(const std::u32string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::STRING_UTF32_VARLEN);
        CheckMaxContainerLength(strsz);

        SerializeContainerLen(_buffer, val.size());
        SerializeUtf32String(_buffer, val);
    }

    void Serializer::SerializeFloat32(std::vector<uint8_t>& buff, float val)
    {
        constexpr auto tsz = sizeof(val);
        
        uint32_t* ptr = reinterpret_cast<uint32_t*>(&val);
        for(int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            _buffer.push_back(byt);
        }            
    }

    void Serializer::Internal_FillContractFloat32(buff_t& buff, float val, int contract_iidx, ContractElemType type)
    {
        CheckContractValidType(contract_iidx, type);
        SerializeFloat32(buff, val);
    }

    void Serializer::SerializeFloat64(std::vector<uint8_t>& buff, double val)
    {
        constexpr auto tsz = sizeof(val);
        
        uint64_t* ptr = reinterpret_cast<uint64_t*>(&val);
        for(int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            _buffer.push_back(byt);
        }            
    }    

    void Serializer::SerializeBoolArray(buff_t& buff, const std::vector<bool>& val)
    {            
        const size_t sz = val.size();
        uint8_t aux = 0x00;
        for(size_t i = 0; i < sz; i++)
        {
            
            if((i % 8 == 0) && (i != 0)) // Byte over
            {
                buff.push_back(aux);
                aux &= 0x00;
            }
            aux |= ((val[i] ? 1 : 0) << (i % 8));
        }
    }

    void Serializer::SerializeUtf16String(buff_t& buff, const std::u16string& val)
    {
        for(size_t i = 0; i < val.size(); i++)
        {
            uint16_t ch = static_cast<uint16_t>(val[i]);
            SerializeIntegral<uint16_t>(buff, ch);
        }
    }

    void Serializer::SerializeUtf32String(buff_t& buff, const std::u32string& val)
    {
        for(size_t i = 0; i < val.size(); i++)
        {
            uint32_t ch = static_cast<uint32_t>(val[i]);
            SerializeIntegral<uint32_t>(buff, ch);
        }
    }

    void Serializer::Internal_FillContractFloat64(std::vector<uint8_t>& buff, double val, int contract_iidx, ContractElemType type)
    {
        CheckContractValidType(contract_iidx, type);
        SerializeFloat64(buff, val);
    }

    void Serializer::CheckContractValidFixedSize(int contract_iidx, int cont_len)
    {
        const ContractElemDesc& desc = _contract.GetElements().at(contract_iidx);
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

    void Serializer::CheckContractValidType(int contract_iidx, ContractElemType type)
    {
        const ContractElemDesc& desc = _contract.GetElements().at(contract_iidx);
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

    void Serializer::SerializeContainerLen(buff_t& buff, size_t cont_len)
    {
        uint16_t len = static_cast<uint16_t>(cont_len);
        SerializeIntegral<uint16_t>(_buffer, len);
    }
}