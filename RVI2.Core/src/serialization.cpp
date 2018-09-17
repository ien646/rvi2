#include "serialization.h"

#include "vector2.h"
#include "color_rgba.h"
#include "vertex.h"
#include "line.h"

namespace rvi
{
    size_t Serializer::SerializeVector2(std::vector<U8>& data_container, const Vector2& val)
    {
        data_container.reserve(data_container.size() + sizeof(Vector2));

        SerializeFloat(data_container, val.X);
        SerializeFloat(data_container, val.Y);

        return (size_t)sizeof(Vector2);
    }
  
    size_t Serializer::SerializeColorRGBA(std::vector<U8>& data_container, const ColorRGBA& val)
    {
        data_container.reserve(data_container.size() + sizeof(ColorRGBA));

        SerializeInteger_Internal(data_container, val.R);
        SerializeInteger_Internal(data_container, val.G);
        SerializeInteger_Internal(data_container, val.B);
        SerializeInteger_Internal(data_container, val.A);

        return (size_t)sizeof(ColorRGBA);
    }

    size_t Serializer::SerializeVertex(std::vector<U8>& data_container, const Vertex& val)
    {
        data_container.reserve(data_container.size() + sizeof(Vertex));

        SerializeVector2(data_container, val.Position);
        SerializeColorRGBA(data_container, val.VertexColor);

        return (size_t)sizeof(Vertex);
    }

    size_t Serializer::SerializeLine(std::vector<U8>& data_container, const Line& val)
    {
        data_container.reserve(sizeof(Line));

        SerializeVertex(data_container, val.Start);
        SerializeVertex(data_container, val.End);

        return sizeof(Line);
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

    Line Serializer::DeserializeLine(const std::vector<U8>& data_container, size_t& offset_ref)
    {
        Line result;

        result.Start = DeserializeVertex(data_container, offset_ref);
        result.End = DeserializeVertex(data_container, offset_ref);

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
