#include "contract_elem_desc.hpp"

namespace rvi::serialization
{
	ContractElemDescriptor::ContractElemDescriptor(ContractElemType type)
		: Type(type)
	{ }	  

	ContractElemDescriptor ContractElemDescriptor::CreateBinary(bool fixed_len, int32_t cont_len)
	{
		ContractElemDescriptor result;
		
		result.ContainerLen = cont_len;
		if (fixed_len)
		{
			result.Type = ContractElemType::BINARY_FIXLEN;
		}
		else
		{
			result.Type = ContractElemType::BINARY_VARLEN;
		}
		return result;
    }
}