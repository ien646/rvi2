#include <vector>
#include <cinttypes>

#include "contract_elem_desc.hpp"

namespace rvi::serialization
{
	class contract
    {
    private:
        std::vector<contract_elem_desc> _contract;
		
    public:
        void append(const contract_elem_desc& desc);
        void append(contract_elem_desc&& desc);

        const std::vector<contract_elem_desc>& get_elements();
    };
}