#include "vertex.hpp"

namespace rvi
{
    Vertex::Vertex(Vector2 pos, ColorRGBA vxColor) noexcept
        : Position(pos)
        , VertexColor(vxColor)
    { }

    Vertex::Vertex(float x, float y) noexcept
        : Position(Vector2(x, y))
    { }

    Vertex::Vertex(float x, float y, U8 r, U8 g, U8 b, U8 a) noexcept
        : Position(Vector2(x, y))
        , VertexColor(ColorRGBA(r, g, b, a))
    { }

    Vertex::Vertex(Vector2 pos) noexcept
        : Position(pos)
    { }

    bool Vertex::operator==(Vertex other) const noexcept
    {
        return (Position == other.Position) && (VertexColor == other.VertexColor);
    }

    bool Vertex::operator!=(Vertex other) const noexcept
    {
        return (Position != other.Position) || (VertexColor != other.VertexColor);
    }
}