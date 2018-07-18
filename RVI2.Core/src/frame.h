/* FILE: frame.h */
#pragma once

#include <vector>
#include <string>
#include <utility>
#include "line.h"
#include "transform2.h"

namespace rvi
{
	class Frame
	{
	public:
		std::string Name;
		std::vector<Line> Lines;
		Transform2 Transform;
		
		Frame() = delete;
		
		Frame(const std::string name);
		
		void ClearLines();
		
		void AddLine(const Line& ln);
		
		void AddLine(Line&& ln);		
	};
}