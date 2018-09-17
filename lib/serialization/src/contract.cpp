#include "contract.hpp"

namespace rvi::serialization
{
    ContractElemDesc::ContractElemDesc(ContractElemType type)
        : Type(type)
    { }

    void Contract::AppendElem(const ContractElemDesc& elem)
    {
        _contract.push_back(elem);
    }

    void Contract::AppendElem(ContractElemDesc&& elem)
    {
        _contract.push_back(std::move(elem));
    }
}