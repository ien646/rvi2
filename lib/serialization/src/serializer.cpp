#include "serializer.hpp"

namespace rvi::serialization
{
    void serializer::fill_contract_scalar_u8(uint8_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_UINT8);
    }

    void serializer::fill_contract_scalar_u16(uint16_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_UINT16);
    }

    void serializer::fill_contract_scalar_u32(uint32_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_UINT32);
    }

    void serializer::fill_contract_scalar_u64(uint64_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_UINT64);
    }

    void serializer::fill_contract_scalar_i8(int8_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_INT8);
    }

    void serializer::fill_contract_scalar_i16(int16_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_INT16);
    }

    void serializer::fill_contract_scalar_i32(int32_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_INT32);
    }

    void serializer::fill_contract_scalar_i64(int64_t val, int contract_iidx)
    {
        i_fill_contract_integral(_buffer, val, contract_iidx, contract_elem_type::SCALAR_INT64);
    }

    void serializer::fill_contract_scalar_fp32(float val, int contract_iidx)
    {
        i_fill_contract_fp32(_buffer, val, contract_iidx, contract_elem_type::SCALAR_FLOAT32);
    }

    void serializer::fill_contract_scalar_fp64(double val, int contract_iidx)
    {
        i_fill_contract_fp64(_buffer, val, contract_iidx, contract_elem_type::SCALAR_FLOAT64);
    }

    void serializer::fill_contract_binary_fixlen(const std::vector<uint8_t>& val, int contract_iidx)
    {
        check_contract_valid_type(contract_iidx, contract_elem_type::BINARY_FIXLEN);
        check_contract_valid_fixed_size(contract_iidx, val.size());

        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void serializer::fill_contract_binary_varlen(const std::vector<uint8_t>& val, int contract_iidx)
    {
        check_contract_valid_type(contract_iidx, contract_elem_type::BINARY_VARLEN);
        check_max_container_len(val.size());

        serialize_container_len(_buffer, val.size());
        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void serializer::fill_contract_bool_array_fixlen(const std::vector<bool>& val, int contract_iidx)
    {
        check_contract_valid_type(contract_iidx, contract_elem_type::BOOL_ARRAY_FIXLEN);
        check_max_container_len(val.size());
        check_contract_valid_fixed_size(contract_iidx, val.size() / sizeof(uint8_t));

        serialize_bool_array(_buffer, val);
    }

    void serializer::fill_contract_bool_array_varlen(const std::vector<bool>& val, int contract_iidx)
    {
        check_contract_valid_type(contract_iidx, contract_elem_type::BOOL_ARRAY_VARLEN);
        check_max_container_len(val.size());

        serialize_container_len(_buffer, val.size());
        serialize_bool_array(_buffer, val);
    }

    void serializer::fill_contract_string_fixlen(const std::string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::STRING_FIXLEN);
        check_contract_valid_fixed_size(contract_iidx, strsz);
        check_max_container_len(strsz);

        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void serializer::fill_contract_string_varlen(const std::string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::STRING_VARLEN);
        check_max_container_len(strsz);

        serialize_container_len(_buffer, strsz);
        std::copy(val.begin(), val.end(), std::back_inserter(_buffer));
    }

    void serializer::fill_contract_u16string_fixlen(const std::u16string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::STRING_UTF16_FIXLEN);
        check_contract_valid_fixed_size(contract_iidx, strsz);
        check_max_container_len(strsz);

        serialize_u16string(_buffer, val);
    }

    void serializer::fill_contract_u16string_varlen(const std::u16string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::STRING_UTF16_VARLEN);
        check_max_container_len(strsz);

        serialize_container_len(_buffer, strsz);
        serialize_u16string(_buffer, val);
    }

    void serializer::fill_contract_u32string_fixlen(const std::u32string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::STRING_UTF32_FIXLEN);
        check_contract_valid_fixed_size(contract_iidx, strsz);
        check_max_container_len(strsz);

        serialize_u32string(_buffer, val);
    }

    void serializer::fill_contract_u32string_varlen(const std::u32string& val, int contract_iidx)
    {
        const size_t strsz = val.size();
        check_contract_valid_type(contract_iidx, contract_elem_type::STRING_UTF32_VARLEN);
        check_max_container_len(strsz);

        serialize_container_len(_buffer, val.size());
        serialize_u32string(_buffer, val);
    }

    void serializer::serialize_fp32(std::vector<uint8_t>& buff, float val)
    {
        constexpr auto tsz = sizeof(val);
        
        uint32_t* ptr = reinterpret_cast<uint32_t*>(&val);
        for(int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            buff.push_back(byt);
        }            
    }

    void serializer::i_fill_contract_fp32(std::vector<uint8_t>& buff, float val, int contract_iidx, contract_elem_type type)
    {
        check_contract_valid_type(contract_iidx, type);
        serialize_fp32(buff, val);
    }

    void serializer::serialize_fp64(std::vector<uint8_t>& buff, double val)
    {
        constexpr auto tsz = sizeof(val);
        
        uint64_t* ptr = reinterpret_cast<uint64_t*>(&val);
        for(int i = 0; i < tsz; i++)
        {
            uint8_t byt = static_cast<uint8_t>((*ptr) >> (i * 8));
            buff.push_back(byt);
        }            
    }    

    void serializer::serialize_bool_array(std::vector<uint8_t>& buff, const std::vector<bool>& val)
    {            
        const size_t sz = val.size();
        uint8_t aux = 0x00;
        for(size_t i = 0; i < sz; i++)
        {
            
            if((i % 8 == 0) && (i != 0)) // Byte over
            {
                buff.push_back(aux);
                aux &= 0x00;
            }
            aux |= ((val[i] ? 1 : 0) << (i % 8));
        }
    }

    void serializer::serialize_u16string(std::vector<uint8_t>& buff, const std::u16string& val)
    {
        for(size_t i = 0; i < val.size(); i++)
        {
            uint16_t ch = static_cast<uint16_t>(val[i]);
            serialize_integral<uint16_t>(buff, ch);
        }
    }

    void serializer::serialize_u32string(std::vector<uint8_t>& buff, const std::u32string& val)
    {
        for(size_t i = 0; i < val.size(); i++)
        {
            uint32_t ch = static_cast<uint32_t>(val[i]);
            serialize_integral<uint32_t>(buff, ch);
        }
    }

    void serializer::i_fill_contract_fp64(std::vector<uint8_t>& buff, double val, int contract_iidx, contract_elem_type type)
    {
        check_contract_valid_type(contract_iidx, type);
        serialize_fp64(buff, val);
    }

    void serializer::check_contract_valid_fixed_size(int contract_iidx, int cont_len)
    {
        const contract_elem_desc& desc = _contract.get_elements().at(contract_iidx);
        if(cont_len > desc.container_len)
        {
            throw_fixed_item_size_overflow(desc, cont_len);
        }
    }  

    void serializer::check_max_container_len(size_t cont_len)
    {
        if(cont_len > std::numeric_limits<uint16_t>::max())
        {
            std::stringstream ss;
            ss  << "Invalid container length. Maximum container length: "
                << std::numeric_limits<uint16_t>::max()
                << ", given length: "
                << cont_len
                << std::endl;
            throw std::logic_error(ss.str());
        }
    }

    void serializer::check_contract_valid_type(int contract_iidx, contract_elem_type type)
    {
        const contract_elem_desc& desc = _contract.get_elements().at(contract_iidx);
        if(type != desc.type)
        {
            throw_invalid_contract_type(desc);
        }
    }

    void serializer::throw_invalid_contract_type(const contract_elem_desc& descriptor)
    {
        std::stringstream ss;
        ss  << "Invalid type for contract. Expected:"
            << static_cast<uint8_t>(descriptor.type)
            << std::endl;
        throw std::logic_error(ss.str());
    }

    void serializer::throw_fixed_item_size_overflow(const contract_elem_desc& descriptor, int cont_sz)
    {
        std::stringstream ss;
        ss << "Invalid container length for fixed size descriptor. Expected (maximum) size: "
            << descriptor.container_len
            << ", given container size: "
            << cont_sz
            << std::endl;
        throw std::logic_error(ss.str());
    }

    void serializer::throw_var_item_size_overflow(int cont_sz)
    {
        std::stringstream ss;
        ss << "Invalid container length for var size descriptor. Expected (maximum) size: "
            << MAX_CONTAINER_LENGTH
            << ", given size: "
            << cont_sz
            << std::endl;
        throw std::logic_error(ss.str());
    }

    void serializer::serialize_container_len(std::vector<uint8_t>& buff, size_t cont_len)
    {
        uint16_t len = static_cast<uint16_t>(cont_len);
        serialize_integral<uint16_t>(buff, len);
    }
}