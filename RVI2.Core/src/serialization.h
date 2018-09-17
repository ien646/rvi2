#pragma once

#include <vector>
#include <cassert>
#include <sstream>
#include <string>

#include "rvi_base.h"

namespace rvi
{
    FWD_DECL_CLASS(Vector2);
    FWD_DECL_CLASS(ColorRGBA);
    FWD_DECL_CLASS(Vertex);

    struct SerializedStringInfo
    {
        size_t CharacterSize;
        size_t StringLength;
    };

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Serializer class
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    class Serializer
    {
        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        // Serialization
        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    public:
        template<typename T, TEMPLATE_ENABLE_IF_IS_INTEGER(T)>
        static size_t SerializeInteger(std::vector<U8>& data_container, const T& val)
        {
            return SerializePOD_Internal(data_container, val);
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_FLOAT(T)>
        static size_t SerializeFloat(std::vector<U8>& data_container, const T& val)
        {
            return SerializePOD_Internal(data_container, val);
        }

        static size_t SerializeVector2(std::vector<U8>& data_container, const Vector2& val);

        static size_t SerializeColorRGBA(std::vector<U8>& data_container, const ColorRGBA& val);

        static size_t SerializeVertex(std::vector<U8>& data_container, const Vertex& val);

        static size_t SerializeString(std::vector<U8>& data_container, const std::string& val);

        static size_t SerializeU16String(std::vector<U8>& data_container, const std::u16string& val);

        static size_t SerializeU32String(std::vector<U8>& data_container, const std::u32string& val);

    private:
        template<typename T, TEMPLATE_ENABLE_IF_IS_POD(T)>
        static size_t SerializePOD_Internal(std::vector<U8>& data_container, const T& pod_obj)
        {
            U8* pod_obj_ptr = (U8*)&pod_obj;
            for (size_t i = 0; i < sizeof(pod_obj); ++i)
            {
                data_container.push_back(pod_obj_ptr[i]);
            }
            return sizeof(T);
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_STRING(T)>
        static size_t SerializeString_Internal(std::vector<U8>& data_container, const T& str_obj)
        {
            const U8 char_sz = (U8)(sizeof(T::value_type));
            const U16 bufflen = (U16)(sizeof(char_sz) + sizeof(U16) + (str_obj.size() * char_sz));
            const size_t stringlen = str_obj.size();

            SerializePOD_Internal<U16>(data_container, bufflen);
            data_container.push_back(char_sz);

            if constexpr(sizeof(T::value_type) == 1)
            {
                std::copy(str_obj.begin(), str_obj.end(), std::back_inserter(data_container));
            }
            else
            {
                for (size_t i = 0; i < stringlen; i++)
                {
                    SerializePOD_Internal<T::value_type>(data_container, str_obj[i]);
                }
            }

            return bufflen;
        }

        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        // Deserialization
        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    public:
        template<typename T, TEMPLATE_ENABLE_IF_IS_INTEGER(T)>
        static T DeserializeInteger(const std::vector<U8>& data_container, size_t& offset_ref)
        {
            return DeserializePOD_Internal<T>(data_container, offset_ref);
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_FLOAT(T)>
        static T DeserializeFloat(const std::vector<U8>& data_container, size_t& offset_ref)
        {
            return DeserializePOD_Internal<T>(data_container, offset_ref);
        }

        static Vector2 DeserializeVector2(const std::vector<U8>& data_container, size_t& offset_ref);

        static ColorRGBA DeserializeColorRGBA(const std::vector<U8>& data_container, size_t& offset_ref);

        static Vertex DeserializeVertex(const std::vector<U8>& data_container, size_t& offset_ref);

        static std::string DeserializeString(const std::vector<U8>& data_container, size_t& offset_ref);

        static std::u16string DeserializeU16String(const std::vector<U8>& data_container, size_t& offset_ref);

        static std::u32string DeserializeU32String(const std::vector<U8>& data_container, size_t& offset_ref);

    private:

        template<typename T, TEMPLATE_ENABLE_IF_IS_POD(T)>
        static T DeserializePOD_Internal(const std::vector<U8>& data_container, size_t& offset_ref)
        {
            size_t obj_sz = sizeof(T);
            assert((offset_ref + obj_sz) <= data_container.size());
            T result;
            std::memcpy(&result, (data_container.data() + offset_ref), obj_sz);
            offset_ref += sizeof(T);
            return result;
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_STRING(T)>
        static T DeserializeString_Internal(const std::vector<U8>& data_container, size_t& offset_ref)
        {
            // Check for out of bounds read attempts
            assert(data_container.size() > (offset_ref + 3));

            const size_t char_size = sizeof(T::value_type);
            
            U16 dataBuffLen = Serializer::DeserializePOD_Internal<U16>(data_container, offset_ref);
            U8 dataCharSz = Serializer::DeserializePOD_Internal<U8>(data_container, offset_ref);

            // Check for char size mismatch
            assert(sizeof(T::value_type) == dataCharSz);

            size_t resultLen = (dataBuffLen - sizeof(dataCharSz) - sizeof(dataBuffLen)) / dataCharSz;

            T result;
            result.reserve(resultLen);

            // If its an std::string just directly copy the data
            if (dataCharSz == 1)
            {
				auto it_begin = (data_container.begin() + offset_ref);
				auto it_end = it_begin + resultLen;
				std::copy(it_begin, it_end, std::back_inserter(result));
				offset_ref += resultLen;
            }
            else
            {
                for (size_t i = 0; i < resultLen; i++)
                {
                    result += Serializer::DeserializePOD_Internal<T::value_type>(data_container, offset_ref);
                }
            }
            return result;
        }
    };
}