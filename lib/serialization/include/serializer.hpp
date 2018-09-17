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

        void FillContractElem(uint8_t val, int elemidx);
        void FillContractElem(uint16_t val, int elemidx);
        void FillContractElem(uint32_t val, int elemidx);
        void FillContractElem(uint64_t val, int elemidx);
        void FillContractElem(int8_t  val, int elemidx);
        void FillContractElem(int16_t val, int elemidx);
        void FillContractElem(int32_t val, int elemidx);
        void FillContractElem(int64_t val, int elemidx);

        void FillContractElem(float val, int elemidx);
        void FillContractElem(double val, int elemidx);

    private:
        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void Internal_FillContractElemIntegral(T val, int elemidx, ContractElemType type)
        {
            
        }

        template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
        void Internal_FillContractElemFloat(T val, int elemidx, ContractElemType type)
        {

        }

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void Internal_SerializeIntegral(T val)
        {

        }

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        void Internal_SerializeFloat(T val)
        {

        }

        template<typename T>
        void CheckContractValidType(int elemidx, ContractElemType type)
        {
            const ContractElemDesc& desc = _contract.GetElements().at(elemidx);
            if(type != desc.Type)
            {
                Throw_InvalidTypeForContract<T>(desc);
            }
        }

        template<typename T>
        void Throw_InvalidTypeForContract(const ContractElemDesc& descriptor)
        {
            std::stringstream ss;
            ss  << "Invalid type for contract. Expected:"
                << descriptor.Type
                << " , Actual:"
                << typeid(T).name();
            throw std::logic_error(ss.str());
        }
    };
}