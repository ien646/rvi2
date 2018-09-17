#include "line.h"

namespace rvi
{
	Line::Line(const Vertex& start, const Vertex& end) noexcept
		: Start(start)
		, End(end)
	{ }

	Line::Line(Vertex&& start, Vertex&& end) noexcept
		: Start(std::move(start))
		, End(std::move(end))
	{ }

	void Line::ApplyTransform(const Transform2& tform) noexcept
	{
		Start.ApplyTransform(tform);
		End.ApplyTransform(tform);
	}
}