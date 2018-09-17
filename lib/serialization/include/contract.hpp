#include <vector>
#include <cinttypes>

#include "contract_elem_desc.hpp"

namespace rvi::serialization
{
	class Contract
    {
    private:
        std::vector<ContractElemDesc> _contract;
		
    public:
        void Append(const ContractElemDesc& desc);
        void Append(ContractElemDesc&& desc);
    };
}
