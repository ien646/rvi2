#include "line.h"

namespace rvi
{
	Line::Line(const Vertex& start, const Vertex& end)
		: Start(start)
		, End(end)
	{

	}

	Line::Line(Vertex&& start, Vertex&& end)
		: Start(std::move(start))
		, End(std::move(end))
	{

	}

	void Line::ApplyTransform(const Transform2& tform)
	{
		Start.ApplyTransform(tform);
		End.ApplyTransform(tform);
	}

}