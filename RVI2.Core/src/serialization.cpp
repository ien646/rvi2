#include "serialization.h"

#include "vector2.h"
#include "color_rgba.h"
#include "vertex.h"

namespace rvi
{
    size_t Serializer::SerializeVector2(std::vector<U8>& data_container, const Vector2& val)
    {
        Serializer::SerializeFloat(data_container, val.X);
        Serializer::SerializeFloat(data_container, val.Y);
        return sizeof(Vector2);
    }

    size_t Serializer::SerializeColorRGBA(std::vector<U8>& data_container, const ColorRGBA& val)
    {
        data_container.push_back(val.R);
        data_container.push_back(val.G);
        data_container.push_back(val.B);
        data_container.push_back(val.A);

        return sizeof(ColorRGBA);
    }

    size_t Serializer::SerializeVertex(std::vector<U8>& data_container, const Vertex& val)
    {
        Serializer::SerializeVector2(data_container, val.Position);
        Serializer::SerializeColorRGBA(data_container, val.VertexColor);
        return sizeof(Vertex);
    }
}