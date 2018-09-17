#include "serializer.hpp"

namespace rvi::serialization
{ 

    void Serializer::operator<<(uint8_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_UINT8);

        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(uint16_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_UINT16);

        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(uint32_t val)
    {        
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_UINT32);
        
        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(uint64_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_UINT64);
        
        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(int8_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_INT8);

        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(int16_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_INT16);

        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(int32_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_INT32);
        
        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(int64_t val)
    {
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_INT64);
        
        _buffer.push_back(header);
        Internal_SerializeIntegral(val);
    }

    void Serializer::operator<<(float val)
    {
        constexpr auto sz = sizeof(val);
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_FLOAT32);
        
        _buffer.push_back(header);
        //
    }

    void Serializer::operator<<(double val)
    {
        constexpr auto sz = sizeof(val);
        constexpr auto header = static_cast<uint8_t>(ContractElemType::SCALAR_FLOAT64);
        
        _buffer.push_back(header);
        //
    }
}