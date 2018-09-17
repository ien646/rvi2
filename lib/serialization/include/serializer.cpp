#include "serializer.hpp"

namespace rvi::serialization
{
    void Serializer::FillContractElem(uint8_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_UINT8);
    }

    void Serializer::FillContractElem(uint16_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_UINT16);
    }

    void Serializer::FillContractElem(uint32_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_UINT32);
    }

    void Serializer::FillContractElem(uint64_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_UINT64);
    }

    void Serializer::FillContractElem(int8_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_INT8);
    }

    void Serializer::FillContractElem(int16_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_INT16);
    }

    void Serializer::FillContractElem(int32_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_INT32);
    }

    void Serializer::FillContractElem(int64_t val, int elemidx)
    {
        Internal_FillContractElemIntegral(val, elemidx, ContractElemType::SCALAR_INT64);
    }

    void Serializer::FillContractElem(float val, int elemidx)
    {
        Internal_FillContractElemFloat(val, elemidx, ContractElemType::SCALAR_FLOAT32);
    }

    void Serializer::FillContractElem(double val, int elemidx)
    {
        Internal_FillContractElemFloat(val, elemidx, ContractElemType::SCALAR_FLOAT64);
    }
}