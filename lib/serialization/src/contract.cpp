#include "contract.hpp"

namespace rvi::serialization
{
    ContractElemDescriptor::ContractElemDescriptor(ContractElemType type)
        : Type(type)
    { }

    void Contract::AppendElem(const ContractElemDescriptor& elem)
    {
        _contract.push_back(elem);
    }

    void Contract::AppendElem(ContractElemDescriptor&& elem)
    {
        _contract.push_back(std::move(elem));
    }
}