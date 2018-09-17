#include <vector>
#include <cinttypes>

#include "contract_elem_desc.hpp"

namespace rvi::serialization
{
	class Contract
    {
    private:
        std::vector<ContractElemDescriptor> _contract;
		
    public:
        void AppendElem(const ContractElemDescriptor& elem);
        void AppendElem(ContractElemDescriptor&& elem);
    };
}
