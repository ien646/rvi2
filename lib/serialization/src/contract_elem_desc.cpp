#include "contract_elem_desc.hpp"

namespace rvi::serialization
{
	ContractElemDesc::ContractElemDesc(ContractElemType type)
		: Type(type)
	{ }	  

	ContractElemDesc ContractElemDesc::CreateBinary(bool fixed_len, int32_t cont_len)
	{
		ContractElemDesc result;		
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

	ContractElemDesc ContractElemDesc::CreateStringUTF8(bool fixed_len, int32_t cont_len)
	{  
		ContractElemDesc result;
		if(fixed_len)
		{
			result.Type = ContractElemType::STRING_UTF8_FIXLEN;
			result.ContainerLen = cont_len;
		}
		else
		{
			result.Type = ContractElemType::STRING_UTF8_VARLEN;
			result.ContainerLen = UNDEFINED_SZ;
		}
		return result;
	}

	ContractElemDesc ContractElemDesc::CreatePackedBoolArray(bool fixed_len, int32_t cont_len)
	{
		ContractElemDesc result;
		if(fixed_len)
		{
			result.ContainerLen = cont_len;
			switch (cont_len)
			{
				case 8:	
					result.Type = ContractElemType::BOOL_ARRAY_FIXLEN_8;
					break;				
				case 16:
					result.Type = ContractElemType::BOOL_ARRAY_FIXLEN_16;
					break;
				case 32:
					result.Type = ContractElemType::BOOL_ARRAY_FIXLEN_32;
					break;
				case 64:
					result.Type = ContractElemType::BOOL_ARRAY_FIXLEN_64;
					break;
				default:
					result.Type = ContractElemType::BOOL_ARRAY_FIXLEN_ARBITRARY;
					break;
			}
		}
		return result;
	}

	ContractElemDesc ContractElemDesc::Internal_CreateString(bool fixed_len, int32_t cont_len)
	{
		ContractElemDesc result;
		if(fixed_len)
		{
			result.ContainerLen = cont_len;
			result.Type = ContractElemType::STRING_FIXLEN;
		}
		else
		{
			result.ContainerLen = UNDEFINED_SZ;
			result.Type = ContractElemType::STRING_VARLEN;
		}
		return result;
	}

	ContractElemDesc ContractElemDesc::Internal_CreateStringUTF16(bool fixed_len, int32_t cont_len)
	{
		ContractElemDesc result;
		if(fixed_len)
		{
			result.ContainerLen = cont_len;
			result.Type = ContractElemType::STRING_UTF16_FIXLEN;
		}
		else
		{
			result.ContainerLen = UNDEFINED_SZ;
			result.Type = ContractElemType::STRING_UTF16_VARLEN;
		}
		return result;
	}

	ContractElemDesc ContractElemDesc::Internal_CreateStringUTF32(bool fixed_len, int32_t cont_len)
	{
		ContractElemDesc result;
		if(fixed_len)
		{
			result.ContainerLen = cont_len;
			result.Type = ContractElemType::STRING_UTF32_FIXLEN;
		}
		else
		{
			result.ContainerLen = UNDEFINED_SZ;
			result.Type = ContractElemType::STRING_UTF32_VARLEN;
		}
		return result;
	}
}