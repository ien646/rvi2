#include <cinttypes>
#include <vector>
#include <type_traits>

#include "base.h"
#include "contract_elem_type.hpp"

namespace rvi::serialization
{
    class Serializer
    {
    private:
        std::vector<uint8_t> _buffer;

    public:
        Serializer() {}
        
        void operator<<(uint8_t val);
        void operator<<(uint16_t val);
        void operator<<(uint32_t val);
        void operator<<(uint64_t val);

        void operator<<(int8_t val);
        void operator<<(int16_t val);
        void operator<<(int32_t val);
        void operator<<(int64_t val);

        void operator<<(float val);
        void operator<<(double val);  

    private:
        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void Internal_SerializeIntegral(T val)
        {
            constexpr auto sz = sizeof(val);
            for(int i = 0; i < sz; i++)
            {
                _buffer.push_back(val << (i * 8));
            }
        }      
    };
}