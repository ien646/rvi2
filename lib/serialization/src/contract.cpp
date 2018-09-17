#include "contract.hpp"

namespace rvi::serialization
{    
    void Contract::Append(const ContractElemDesc& desc)
    {
        _contract.push_back(desc);
    }

    void Contract::Append(ContractElemDesc&& desc)
    {
        _contract.push_back(std::move(desc));
    }
}