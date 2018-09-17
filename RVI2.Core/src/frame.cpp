#include "frame.h"

namespace rvi
{
	Frame::Frame(const std::string name)
		: Name(name)
	{ }

	void Frame::ClearLines()
	{
		Lines.clear();
	}

	void Frame::AddLine(const Line& ln)
	{
		Lines.push_back(ln);
	}

	void Frame::AddLine(Line&& ln)
	{
		Lines.push_back(std::move(ln));
	}

	void Frame::AddChildFrame(const std::string& name)
	{
		ChildFrames.emplace_back(name);
	}

	void Frame::AddChildFrame(std::string&& name)
	{
		ChildFrames.emplace_back(std::move(name));
	}

	void Frame::GetModulatedLines(std::vector<Line>& result, const Transform2& parentTform)
	{
		// Current absolute transform
		Transform2 absTform = Transform.Merge(parentTform);

		// Owned lines
		std::vector<Line> ownLines;
		ownLines.reserve(Lines.size());
		absTform.ApplyTo(ownLines);
		std::move(ownLines.begin(), ownLines.end(), std::back_inserter(result));

		// Child frames
		for (auto& chFrame : ChildFrames)
		{
			chFrame.GetModulatedLines(result, absTform);
		}
	}
}