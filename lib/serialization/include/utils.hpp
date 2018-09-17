#include <cinttypes>
#include <vector>

#include "serialization_base.h"

namespace rvi::serialization
{
	template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
	std::vector<uint8_t> SerializeScalar(const T& val)
	{
		constexpr auto sz = sizeof(T);
		std::vector<uint8_t> result;
		result.reserve(sz)
		
		for(int i = 0; i < sz; i++)
		{
			result.push_back(static_cast<uint8_t>(val >> (i * 8)); 
		}
		
		return result;
	}
}