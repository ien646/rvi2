#include "frame.h"

namespace rvi
{

	rvi::Frame::Frame(const std::string name)
		: Name(name)
	{

	}

	void rvi::Frame::ClearLines()
	{
		Lines.clear();
	}

	void rvi::Frame::AddLine(const Line& ln)
	{
		Lines.push_back(ln);
	}

	void rvi::Frame::AddLine(Line&& ln)
	{
		Lines.push_back(std::move(ln));
	}

}