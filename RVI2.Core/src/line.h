/* FILE: line.h */
#pragma once

#include "rviTypes.h"
#include "vertex.h"

#include <utility>

namespace rvi
{
	class Line
	{
	public:
		Vertex Start;
		Vertex End;
		
		constexpr Line() noexcept { }
		
		Line(const Vertex& start, const Vertex& end);
		
		Line(Vertex&& start, Vertex&& end);
	};
}