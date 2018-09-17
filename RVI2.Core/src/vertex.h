/* FILE: vertex2.h */
#pragma once

#include "rviTypes.h"
#include "vector2.h"
#include "colorRgba.h"

namespace rvi
{
    class Vertex
    {
    public:
        Vector2 Position;
        ColorRGBA VertexColor;

        constexpr Vertex() noexcept { }

        Vertex(float x, float y) noexcept;

        Vertex(float x, float y, U8 r, U8 g, U8 b, U8 a) noexcept;

        Vertex(Vector2 pos) noexcept;

        Vertex(Vector2 pos, ColorRGBA vxColor) noexcept;

        void ApplyTransform(const Transform2& tform) noexcept;
    };
}