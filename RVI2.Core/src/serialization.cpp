#include "serialization.h"

#include "vector2.h"
#include "color_rgba.h"
#include "vertex.h"

namespace rvi
{
    size_t Serializer::SerializeVector2(std::vector<U8>& data_container, const Vector2& val)
    {
        data_container.reserve(data_container.size() + sizeof(Vector2));

        Serializer::SerializeFloat(data_container, val.X);
        Serializer::SerializeFloat(data_container, val.Y);

        return sizeof(Vector2);
    }

    size_t Serializer::SerializeColorRGBA(std::vector<U8>& data_container, const ColorRGBA& val)
    {
        data_container.reserve(data_container.size() + sizeof(ColorRGBA));

        data_container.push_back(val.R);
        data_container.push_back(val.G);
        data_container.push_back(val.B);
        data_container.push_back(val.A);

        return sizeof(ColorRGBA);
    }

    size_t Serializer::SerializeVertex(std::vector<U8>& data_container, const Vertex& val)
    {
        data_container.reserve(data_container.size() + sizeof(Vertex));

        Serializer::SerializeVector2(data_container, val.Position);
        Serializer::SerializeColorRGBA(data_container, val.VertexColor);

        return sizeof(Vertex);
    }

    size_t Serializer::SerializeString(std::vector<U8>& data_container, const std::string& val)
    {
        data_container.reserve(data_container.size() + (val.size() * sizeof(std::string::value_type)) + 1);
        return SerializeString_Internal<std::string>(data_container, val);
    }

    size_t Serializer::SerializeU16String(std::vector<U8>& data_container, const std::u16string & val)
    {
        data_container.reserve(data_container.size() + (val.size() * sizeof(std::u16string::value_type)) + 1);
        return SerializeString_Internal<std::u16string>(data_container, val);
    }

    size_t Serializer::SerializeU32String(std::vector<U8>& data_container, const std::u32string & val)
    {
        data_container.reserve(data_container.size() + (val.size() * sizeof(std::u32string::value_type)) + 1);
        return SerializeString_Internal<std::u32string>(data_container, val);
    }

    Vector2 Serializer::DeserializeVector2(const std::vector<U8>& data_container, size_t& offset)
    {
        Vector2 result;

        result.X = DeserializeFloat<float>(data_container, offset);
        result.Y = DeserializeFloat<float>(data_container, offset);

        return result;
    }

    ColorRGBA Serializer::DeserializeColorRGBA(const std::vector<U8>& data_container, size_t& offset)
    {
        ColorRGBA result;

        result.R = DeserializeInteger<U8>(data_container, offset);
        result.G = DeserializeInteger<U8>(data_container, offset);
        result.B = DeserializeInteger<U8>(data_container, offset);
        result.A = DeserializeInteger<U8>(data_container, offset);

        return result;
    }

    Vertex Serializer::DeserializeVertex(const std::vector<U8>& data_container, size_t& offset)
    {
        Vertex result;

        result.Position = DeserializeVector2(data_container, offset);
        result.VertexColor = DeserializeColorRGBA(data_container, offset);

        return result;
    }

    std::string Serializer::DeserializeString(const std::vector<U8>& data_container, size_t& offset)
    {
        return DeserializeString_Internal<std::string>(data_container, offset);
    }

    std::u16string Serializer::DeserializeU16String(const std::vector<U8>& data_container, size_t& offset)
    {
        return DeserializeString_Internal<std::u16string>(data_container, offset);
    }

    std::u32string Serializer::DeserializeU32String(const std::vector<U8>& data_container, size_t& offset)
    {
        return DeserializeString_Internal<std::u32string>(data_container, offset);
    }
}