namespace rvi::serialization
{
    template<typename T, 
                 typename = std::enable_if_t<std::is_integral_v<T> 
                 || std::is_floating_point_v<T>>>
    static constexpr ContractElemDesc CreateScalar()
    {
        if constexpr(std::is_integral_v<T>)
        {
            return I_CreateScalar_Integer<T>();
        }
        else
        {
            return I_CreateScalar_Float<T>();
        }
        return result;
    }

    static constexpr ContractElemDesc CreateBinary(bool fixed_len, int32_t cont_len)
    {
        ContractElemDesc result;
        if(fixed_len)
        {
            result.ContainerLen = cont_len;
            result.Type = ContractElemType::BINARY_FIXLEN;
        }
        else
        {
            result.ContainerLen= ContractElemDesc::UNDEFINED_SZ; 
            result.Type = ContractElemType::BINARY_VARLEN;
        }
        return result;
    }

    template<typename T, 
                typename = std::enable_if_t<std::is_integral_v<T> 
                || std::is_floating_point_v<T>>>
    static constexpr ContractElemDesc CreateArray(bool fixed_len, int32_t cont_len)
    {
        ContractElemDesc result;
        constexpr auto sz = static_cast<int32_t>(sizeof(T));
        result.ItemSize = sz;

        if(fixed_len)
        {
            result.ContainerLen = cont_len;
            result.Type = ContractElemType::ARRAY_SCALAR_FIXLEN;
        }
        else
        {
            result.ContainerLen = ContractElemDesc::UNDEFINED_SZ;
            result.Type = ContractElemType::ARRAY_SCALAR_VARLEN;
        }        
        return result;
    }

    static constexpr ContractElemDesc CreatePackedBoolArray(bool fixed_len, int32_t cont_len)
    {
        ContractElemDesc result;
        if(fixed_len)
        {
            result.ContainerLen = cont_len;
            result.Type = ContractElemType::BOOL_ARRAY_FIXLEN;
        }
        else
        {
            result.ContainerLen = ContractElemDesc::UNDEFINED_SZ;
            result.Type = ContractElemType::BOOL_ARRAY_VARLEN;
        }
        return result;
    }

    template<typename T, typename std::enable_if_t<
            std::is_same_v<std::basic_string<typename T::value_type>, T>>>
    static constexpr ContractElemDesc CreateString(bool fixed_len, int32_t cont_len)
    {
        if constexpr(std::is_same_v<std::string::value_type, T::value_type>)
        {
            I_CreateString(fixed_len, cont_len);
        }
        else if constexpr(std::is_same_v<std::ju16string::value_type, T::value_type>)
        {
            I_CreateStringUTF16(fixed_len, cont_len);
        }
        else if constexpr(std::is_same_v<std::u32string::value_type, T::value_type>)
        {
            I_CreateStringUTF32(fixed_len, cont_len);
        }
        else
        {
            static_assert(0, "Unknown string character size/type");
        }
    }

    static constexpr ContractElemDesc I_CreateStringUTF32(bool fixed_len, int32_t cont_len)
    {
        ContractElemDesc result;
        if(fixed_len)
        {
            result.ContainerLen = cont_len;
            result.Type = ContractElemType::STRING_UTF32_FIXLEN;
        }
        else
        {
            result.ContainerLen = ContractElemDesc::UNDEFINED_SZ;
            result.Type = ContractElemType::STRING_UTF32_VARLEN;
        }
        return result;
    }        

    static constexpr ContractElemDesc I_CreateStringUTF16(bool fixed_len, int32_t cont_len)
    {
        ContractElemDesc result;
        if(fixed_len)
        {
            result.ContainerLen = cont_len;
            result.Type = ContractElemType::STRING_UTF16_FIXLEN;
        }
        else
        {
            result.ContainerLen = ContractElemDesc::UNDEFINED_SZ;
            result.Type = ContractElemType::STRING_UTF16_VARLEN;
        }
        return result;
    }

    static constexpr ContractElemDesc I_CreateString(bool fixed_len, int32_t cont_len)
    {
        ContractElemDesc result;
        if(fixed_len)
        {
            result.ContainerLen = cont_len;
            result.Type = ContractElemType::STRING_FIXLEN;
        }
        else
        {
            result.ContainerLen = ContractElemDesc::UNDEFINED_SZ;
            result.Type = ContractElemType::STRING_VARLEN;
        }
        return result;
    }

    template<typename T>
    static constexpr ContractElemDesc I_CreateScalar_Float()
    {
        static_assert(std::is_floating_point_v<T>);
        constexpr auto sz = sizeof(T);

        static_assert(
            sz == 4 ||
            sz == 8,
            "Invalid scalar floating-point size for ContractElemDesc"
        );

        ContractElemDesc result;
        if constexpr(sz == 4)
            result.Type = ContractElemType::SCALAR_FLOAT32;
        else if constexpr(sz == 8)
            result.Type = ContractElemType::SCALAR_FLOAT64;

        return result;
    }

    template<typename T>
    static constexpr ContractElemDesc I_CreateScalar_Integer()
    {
        static_assert(std::is_integral_v<T>, "Type is not integral");
        constexpr auto sz = sizeof(T);

        static_assert(
            sz == 1 ||
            sz == 2 ||
            sz == 4 ||
            sz == 8,
            "Invalid scalar integer size for ContractElemDesc"
        );
        
        ContractElemDesc result;
        result.ItemSize = sizeof(T);
        if constexpr(std::is_signed_v<T>)
        {
            if constexpr(sz == 1)
                result.Type = ContractElemType::SCALAR_INT8;
            else if constexpr(sz == 2)
                result.Type = ContractElemType::SCALAR_INT16;
            else if constexpr(sz == 4)
                result.Type = ContractElemType::SCALAR_INT32;
            else if constexpr(sz == 8)
                result.Type = ContractElemType::SCALAR_INT64;
        }
        else
        {
            if constexpr(sz == 1)
                result.Type = ContractElemType::SCALAR_UINT8;
            else if constexpr(sz == 2)
                result.Type = ContractElemType::SCALAR_UINT16;
            else if constexpr(sz == 4)
                result.Type = ContractElemType::SCALAR_UINT32;
            else if constexpr(sz == 8)
                result.Type = ContractElemType::SCALAR_UINT64;
        }
        return result;
    }
}