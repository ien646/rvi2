#include "vertex.h"

rvi::Vertex::Vertex(Vector2 pos, ColorRGBA vxColor) 
	: Position(pos)
	, VertexColor(vxColor)
{ }

rvi::Vertex::Vertex(float x, float y) 
	: Position(Vector2(x, y))
{ }

rvi::Vertex::Vertex(float x, float y, U8 r, U8 g, U8 b, U8 a) 
	: Position(Vector2(x, y))
	, VertexColor(Color(r, g, b, a))
{ }

rvi::Vertex::Vertex(Vector2 pos) 
	: Position(pos)
{ }

void rvi::Vertex::ApplyTransform(const Transform2& tform)
{
	Position.ApplyTransform(tform);
}
