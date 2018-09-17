namespace rvi::serialization
{
    template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
    void FillContractArray_FixLen(const std::vector<T>& val, int contract_iidx)
    {
        const auto cont_len = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::ARRAY_SCALAR_FIXLEN);
        CheckMaxContainerLength(cont_len);

        SerializeArray(_buffer, val);
    }

    template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
    void FillContractArray_VarLen(const std::vector<T>& val, int contract_iidx)
    {
        const auto cont_len = val.size();
        CheckContractValidType(contract_iidx, ContractElemType::ARRAY_SCALAR_VARLEN);
        CheckMaxContainerLength(cont_len);
        
        SerializeContainerLen(_buffer, cont_len);
        SerializeArray(_buffer, val);
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    void I_FillContractIntegral(std::vector<uint8_t>& buff, T val, int contract_iidx, ContractElemType type)
    {
        CheckContractValidType(contract_iidx, type);
        SerializeIntegral(buff, val);
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    void SerializeIntegral(std::vector<uint8_t>& buff, T val)
    {
        constexpr auto tsz = sizeof(T);
        if constexpr(tsz == sizeof(uint8_t))
        {
            _buffer.push_back(val);
        }
        else
        {
            for(int i = 0; i < tsz; i++)
            {
                uint8_t byt = static_cast<uint8_t>(val >> (i * 8));
                _buffer.push_back(byt);
            }
        }
    }

    template<typename T, typename = std::enable_if_t<IsScalarType<T>()>>
    void SerializeArray(std::vector<uint8_t>& buff, const std::vector<T>& val)
    {
        for (int i = 0; i < cont_len; i++)
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                SerializeFloat(buff, val[i]);
            }
            else
            {
                SerializeIntegral(buff, val[i]);
            }
        }
    }
}