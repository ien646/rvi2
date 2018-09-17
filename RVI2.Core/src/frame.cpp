#include "frame.h"

namespace rvi
{
	Frame::Frame(const std::string& name)
		: _name(name)
	{ }

	Frame::Frame(std::string&& name)
		: _name(std::move(name))
	{ }

	void Frame::ClearLines()
	{
		_lines.clear();
	}

	void Frame::AddLine(const Line& ln)
	{
		_lines.push_back(ln);
	}

	void Frame::AddLine(Line&& ln)
	{
		_lines.push_back(std::move(ln));
	}

	void Frame::AddChildFrame(const std::string& name)
	{
		_childFrames.emplace_back(name);
	}

	void Frame::AddChildFrame(std::string&& name)
	{
		_childFrames.emplace_back(std::move(name));
	}

	void Frame::GetModulatedLines(std::vector<Line>& result, const Transform2& parentTform)
	{
		// Current absolute transform
		Transform2 absTform = _transform.Merge(parentTform);

		// Owned lines
		std::vector<Line> ownLines;
		ownLines.reserve(_lines.size());
		absTform.ApplyTo(ownLines);
		std::move(ownLines.begin(), ownLines.end(), std::back_inserter(result));

		// Child frames
		for (auto& chFrame : _childFrames)
		{
			chFrame.GetModulatedLines(result, absTform);
		}
	}

	void Frame::SetColor(U8 r, U8 g, U8 b, U8 a)
	{
		_color = ColorRGBA(r, g, b, a);
	}

	void Frame::SetColor(ColorRGBA color)
	{
		_color = color;
	}

	void Frame::SetTransform(const Transform2& tform)
	{
		_transform = tform;
	}

	void Frame::SetTransform(Transform2&& tform)
	{
		_transform = std::move(tform);
	}

	const std::string& Frame::Name() const noexcept
	{
		return _name;
	}

	const std::vector<Line>& Frame::Lines() const noexcept
	{
		return _lines;
	}

	const std::vector<Frame>& Frame::Frames() const noexcept
	{
		return _childFrames;
	}

	const Transform2& Frame::Transform() const noexcept
	{
		return _transform;
	}

	ColorRGBA Frame::Color() const noexcept
	{
		return _color;
	}

}