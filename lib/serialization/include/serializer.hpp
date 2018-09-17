#include <cinttypes>
#include <vector>
#include <type_traits>
#include <sstream>

#include "base.hpp"
#include "contract.hpp"

namespace rvi::serialization
{
    class Serializer
    {
    private:
        std::vector<uint8_t> _buffer;
    	Contract _contract;

    public:
        Serializer(const Contract& contract)
            : _contract(contract)
        { }

        Serializer(Contract&& contract)
            : _contract(std::move(contract))
        { }

        void FillContractElem(uint8_t val, int elemidx)
        {
            ContractElemDesc desc = _contract.GetElements().at(elemidx);
            if(desc.Type != ContractElemType::SCALAR_UINT8)
            {
                std::stringstream ss;
                ss  << "Invalid type for given contract index element. Expected type: " 
                    << (uint8_t)desc.Type 
                    << "; Actual type: " 
                    << typeid(val).name();
                throw std::logic_error(ss.str());
            }
            _buffer.push_back(val);
        }
    };
}