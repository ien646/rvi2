#include <ciinttypes>
#include <vector>

template<typename T, std::enable_if_t<std::is_integral_v<T>>>
std::vector<uint8_t> SerializeInteger(const T& val)
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