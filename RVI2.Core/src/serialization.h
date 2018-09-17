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

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Serializer class
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    class Serializer
    {
    public:
        template<typename T, TEMPLATE_ENABLE_IF_IS_INTEGER(T)>
        static size_t SerializeInteger(std::vector<U8>& data_container, const T& val)
        {
            return SerializePOD(data_container, val);
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_FLOAT(T)>
        static size_t SerializeFloat(std::vector<U8>& data_container, const T& val)
        {
            return SerializePOD(data_container, val);
        }

        static size_t SerializeVector2(std::vector<U8>& data_container, const Vector2& val);

        static size_t SerializeColorRGBA(std::vector<U8>& data_container, const ColorRGBA& val);

        static size_t SerializeVertex(std::vector<U8>& data_container, const Vertex& val);

        static size_t SerializeString(std::vector<U8>& data_container, const std::string& val);

    private:
        template<typename T, TEMPLATE_ENABLE_IF_IS_POD(T)>
        static size_t SerializePOD(std::vector<U8>& data_container, const T& pod_obj)
        {
            U8* pod_obj_ptr = (U8*)&pod_obj;
            for (size_t i = 0; i < sizeof(pod_obj); ++i)
            {
                data_container.push_back(pod_obj_ptr[i]);
            }
            return sizeof(T);
        }

        template<typename T, TEMPLATE_ENABLE_IF_IS_STRING(T)>
        static size_t SerializeString(std::vector<U8>& data_container, const T& str)
        {
            // Total buffer size (string-size * character-size + character-size byte header)
            U16 buff_sz = (U16)(str.size() * char_sz) + 1;

            // Get string character size
            U8 char_sz = (U8)(sizeof(str.value_type()));

            // Push buffer size and character size to the container
            Serializer::SerializeInteger<U8>(data_container, buff_sz);
            Serializer::SerializeInteger<U16>(data_container, char_sz);

            if (char_sz == 1)
            {
                std::copy(str.begin(), str.end(), std::back_inserter(data_container));
            }
            else
            {
                // Iterate the string characters and push each character byte to the container
                for (auto it = str.begin(); it != str.end(); it++)
                {
                    U8* charPtr = (U8*)(&(*it));
                    for (size_t i = 0; i < char_sz; i++)
                    {
                        data_container.push_back(charPtr[i]);
                    }
                }
            }
            return buff_sz;
        }
    };
}