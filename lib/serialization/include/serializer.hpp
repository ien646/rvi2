#include <cinttypes>
#include <vector>
#include <type_traits>
#include <sstream>
#include <limits>

#include "contract.hpp"
#include "template_helpers.hpp"

namespace rvi::serialization
{
    class serializer
    {
    private:
        std::vector<uint8_t> _buffer;
    	contract _contract;

        const uint32_t MAX_CONTAINER_LENGTH = 
            static_cast<uint32_t>(std::numeric_limits<uint16_t>::max());

    public:
        serializer(const contract& contract)
            : _contract(contract)
        { }

        serializer(contract&& contract)
            : _contract(std::move(contract))
        { }

        void fill_contract_scalar_u8(uint8_t val, int contract_iidx);
        void fill_contract_scalar_u16(uint16_t val, int contract_iidx);
        void fill_contract_scalar_u32(uint32_t val, int contract_iidx);
        void fill_contract_scalar_u64(uint64_t val, int contract_iidx);
        void fill_contract_scalar_i8(int8_t val, int contract_iidx);
        void fill_contract_scalar_i16(int16_t val, int contract_iidx);
        void fill_contract_scalar_i32(int32_t val, int contract_iidx);
        void fill_contract_scalar_i64(int64_t val, int contract_iidx);

        void fill_contract_scalar_fp32(float val, int contract_iidx);
        void fill_contract_scalar_fp64(double val, int contract_iidx);

        void fill_contract_binary_fixlen(const std::vector<uint8_t>& val, int contract_iidx);
        void fill_contract_binary_varlen(const std::vector<uint8_t>& val, int contract_iidx);

        template<typename T, typename = enable_if_float_or_integral<T>>
        void fill_contract_array_fixlen(const std::vector<T>& val, int contract_iidx);

        template<typename T, typename = enable_if_float_or_integral<T>>
        void fill_contract_array_varlen(const std::vector<T>& val, int contract_iidx);

        void fill_contract_bool_array_fixlen(const std::vector<bool>& val, int contract_iidx);
        void fill_contract_bool_array_varlen(const std::vector<bool>& val, int contract_iidx);

        void fill_contract_string_fixlen(const std::string& val, int contract_iidx);
        void fill_contract_string_varlen(const std::string& val, int contract_iidx);

        void fill_contract_u16string_fixlen(const std::u16string& val, int contract_iidx);
        void fill_contract_u16string_varlen(const std::u16string& val, int contract_iidx);

        void fill_contract_u32string_fixlen(const std::u32string& val, int contract_iidx);
        void fill_contract_u32string_varlen(const std::u32string& val, int contract_iidx);

    private:
        void check_contract_valid_fixed_size(int contract_iidx, int cont_len);
        void check_contract_valid_var_size(int cont_len);
        void check_contract_valid_type(int contract_iidx, contract_elem_type type);
        void check_max_container_len(size_t cont_len);

        void throw_invalid_contract_type(const contract_elem_desc& descriptor);
        void throw_fixed_item_size_overflow(const contract_elem_desc& descriptor, int cont_sz);
        void throw_var_item_size_overflow(int cont_sz);

        template<typename T, typename = enable_if_integral<T>>
        void i_fill_contract_integral(std::vector<uint8_t>& buff, T val, int contract_iidx, contract_elem_type type);

        void i_fill_contract_fp32(std::vector<uint8_t>& buff, float val, int contract_iidx, contract_elem_type type);
        void i_fill_contract_fp64(std::vector<uint8_t>& buff, double val, int contract_iidx, contract_elem_type type);

        template<typename T, typename = enable_if_integral<T>>
        void serialize_integral(std::vector<uint8_t>& buff, T val);

        void serialize_fp32(std::vector<uint8_t>& buff, float val);
        void serialize_fp64(std::vector<uint8_t>& buff, double val);

        template<typename T, typename = enable_if_float_or_integral<T>>
        void serialize_array(std::vector<uint8_t>& buff, const std::vector<T>& val);

        void serialize_bool_array(std::vector<uint8_t>& buff, const std::vector<bool>& val);
        void serialize_u16string(std::vector<uint8_t>& buff, const std::u16string& val);
        void serialize_u32string(std::vector<uint8_t>& buff, const std::u32string& val);
        void serialize_container_len(std::vector<uint8_t>& buff, size_t cont_len);
    };


///////////////////////////////////////////////////////////////////////
// INLINE/TEMPLATE DEFINITIONS
///////////////////////////////////////////////////////////////////////

    template<typename T, typename>
    void serializer::fill_contract_array_fixlen(const std::vector<T>& val, int contract_iidx)
    {
        const auto cont_len = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::ARRAY_SCALAR_FIXLEN);
        check_max_container_len(cont_len);

        serialize_array(_buffer, val);
    }

    template<typename T, typename>
    void serializer::fill_contract_array_varlen(const std::vector<T>& val, int contract_iidx)
    {
        const auto cont_len = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::ARRAY_SCALAR_VARLEN);
        check_max_container_len(cont_len);
        
        serialize_container_len(_buffer, cont_len);
        serialize_array(_buffer, val);
    }

    template<typename T, typename>
    void serializer::i_fill_contract_integral(std::vector<uint8_t>& buff, T val, int contract_iidx, contract_elem_type type)
    {
        check_contract_valid_type(contract_iidx, type);
        serialize_integral(buff, val);
    }

    template<typename T, typename>
    void serializer::serialize_integral(std::vector<uint8_t>& buff, T val)
    {
        constexpr auto tsz = sizeof(T);
        if constexpr(tsz == sizeof(uint8_t))
        {
            buff.push_back(val);
        }
        else
        {
            for(int i = 0; i < tsz; i++)
            {
                uint8_t byt = static_cast<uint8_t>(val >> (i * 8));
                buff.push_back(byt);
            }
        }
    }

    template<typename T, typename>
    void serializer::serialize_array(std::vector<uint8_t>& buff, const std::vector<T>& val)
    {
        for (int i = 0; i < cont_len; i++)
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                SerializeFloat(buff, val[i]);
            }
            else
            {
                serialize_integral(buff, val[i]);
            }
        }
    }
}