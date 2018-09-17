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

    private:
        template<typename T, TEMPLATE_ENABLE_IF_IS_POD(T)>
        static size_t SerializePOD_Internal(std::vector<U8>& data_container, const T& pod_obj)
        {
            // Resize container to fit new data
            data_container.reserve(data_container.size() + sizeof(T));

            U8* pod_obj_ptr = (U8*)&pod_obj;
            for (size_t i = 0; i < sizeof(pod_obj); ++i)
            {
                data_container.push_back(pod_obj_ptr[i]);
            }
            return sizeof(T);
        }

        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        // Deserialization
        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    public:
        static std::string DeserializeString(const std::vector<U8>& data_container, size_t offset)
        {
            return DeserializeString_Internal<std::string>(data_container, offset);
        }

        static std::wstring DeserializeWString(const std::vector<U8>& data_container, size_t offset)
        {
            return DeserializeString_Internal<std::wstring>(data_container, offset);
        }

    private:

        template<typename T, TEMPLATE_ENABLE_IF_IS_POD(T)>
        static T DeserializePOD_Internal(const std::vector<U8>& data_container, size_t offset)
        {
            size_t obj_sz = sizeof(T);
            assert((offset + obj_sz) <= data_container.size());
            T result;
            std::memcpy(&result, (data_container.data() + offset), obj_sz);
            return result;
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_STRING(T)>
        static T DeserializeString_Internal(const std::vector<U8>& data_container, size_t offset)
        {
            // Check for out of bounds read attempts
            assert(data_container.size() < (offset + 3));

            const size_t char_size = sizeof(T::value_type);

            // Check for char size mismatch
            assert(sizeof(T::value_type) == char_size);

            size_t currentOffset = offset;

            U16 dataBuffLen = Serializer::DeserializePOD_Internal<U16>(data_container, currentOffset);
            currentOffset += sizeof(dataBuffLen);

            U8 dataCharSz = data_container[currentOffset];
            currentOffset += sizeof(dataCharSz);

            size_t resultLen = (dataBuffLen - sizeof(dataCharSz)) / dataCharSz;

            T result;
            result.reserve(resultLen);

            // If its an std::string just directly copy the data
            if (dataCharSz == 1)
            {
                auto container_it_begin = (data_container.begin() + currentOffset);
                auto container_it_end = container_it_begin + (resultLen * char_size);
                DISCARD_RESULT std::copy(container_it_begin, container_it_end, result.begin());
            }
            else
            {
                for (size_t i = 0; i < resultLen; i++)
                {
                    result += Serializer::DeserializePOD_Internal<T::value_type>(data_container, currentOffset);
                    currentOffset += char_size;
                }
            }
            return result;
        }
    };
}