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
		std::vector<Frame> ChildFrames;
		Transform2 Transform;
		
		Frame() = delete;
		
		Frame(const std::string name);
		
		void ClearLines();
		
		void AddLine(const Line& ln);
		
		void AddLine(Line&& ln);

		void AddChildFrame(const std::string& name);

		void AddChildFrame(std::string&& name);

		void GetModulatedLines(std::vector<Line>& result, const Transform2& parentTform)
		{
			// First, add owned lines, applying own transform

		}
	};
}