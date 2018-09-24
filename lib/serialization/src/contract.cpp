#include "contract.hpp"

namespace rvi::serialization
{    
    void contract::append(const contract_elem_desc& desc)
    {
        _contract.push_back(desc);
    }

    void contract::append(contract_elem_desc&& desc)
    {
        _contract.push_back(std::move(desc));
    }

    const std::vector<contract_elem_desc>& contract::get_elements()
    {
        return _contract;
    }
}