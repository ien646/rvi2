/* FILE: vertex2.h */
#pragma once

#include "rviTypes.h"
#include "vector2.h"
#include "color.h"

namespace rvi
{
	class Vertex
	{
	public:
		Vector2 Position;
		Color VertexColor;
		
		constexpr Vertex() noexcept { }
		
		Vertex(float x, float y);
		
		Vertex(float x, float y, U8 r, U8 g, U8 b, U8 a);
		
		Vertex(Vector2 pos);
		
		Vertex(Vector2 pos, Color vxColor);

		void ApplyTransform(const Transform2& tform);
	};
}
