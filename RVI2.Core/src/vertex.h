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
		
		// ------------ Constructors ------------
		
		constexpr Vertex() noexcept { }
		
		Vertex(FLOAT x, FLOAT y)
			: Position(Vector2(x, y))
		{ }
		
		Vertex(FLOAT x, FLOAT y, U8 r, U8 g, U8 b, U8 a)
			: Position(Vector2(x, y))
			, VertexColor(Color(r, g, b, a))
		{ }
		
		Vertex(Vector2 pos)
			: Position(pos)
		{ }
		
		Vertex(Vector2 pos, Color vxColor)
			: Position(pos)
			, VertexColor(vxColor)
		{ }
	};
}
