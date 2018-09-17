#include <vector>
#include <cinttypes>

#include "contract_elem_type.hpp"

namespace rvi::serialization
{
    struct ContractElemDescriptor
    {
        ContractElemType Type;
        int32_t ItemSize        = -1;
        int32_t ContainerLen    = -1;
        int32_t ArrayFixedLen   = -1;

        ContractElemDescriptor() = delete;
        ContractElemDescriptor(ContractElemType type);
    };

	class Contract
    {
    private:
        std::vector<ContractElemDescriptor> _contract;
		
	public:
		void Contract::AppendElem(const ContractElemDescriptor& elem);
        void Contract::AppendElem(ContractElemDescriptor&& elem);
    };
}