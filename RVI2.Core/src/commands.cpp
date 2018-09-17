#include "commands.h"
#include "serializer.h"

namespace rvi
{
	Command_Nop::Command_Nop() noexcept
	{
		Header = (U8)RVI_COMMAND_HEADER::NOP;
	}

	void Command_Nop::BuildData()
	{
		return;
	}

	Command_RequestAck::Command_RequestAck(U16 reqId)
	{ 
		Header = (U8)RVI_COMMAND_HEADER::REQUEST_ACK;
		RequestId = reqId;
	}

	void Command_RequestAck::BuildData()
	{
		AppendData(Serializer::GetBytes(RequestId));
	}

	Command_ResponseAck::Command_ResponseAck(U16 reqId)
	{
		Header = (U8)RVI_COMMAND_HEADER::RESPONSE_ACK;
		RequestId = reqId;
	}

	void Command_ResponseAck::BuildData()
	{
		AppendData(Serializer::GetBytes(RequestId));
	}

	Command_DrawLine::Command_DrawLine(const Vertex& vxFrom, const Vertex& vxTo)
	{
		Header = (U8)RVI_COMMAND_HEADER::DRAW_LINE;
		VxFrom = vxFrom;
		VxTo = vxTo;
	}

	Command_DrawLine::Command_DrawLine(Vertex&& vxFrom, Vertex&& vxTo)
	{
		Header = (U8)RVI_COMMAND_HEADER::DRAW_LINE;
		VxFrom = std::move(vxFrom);
		VxTo = std::move(vxTo);
	}

	void Command_DrawLine::BuildData()
	{
		AppendData(Serializer::GetBytes(VxFrom));
		AppendData(Serializer::GetBytes(VxTo));
	}

	Command_SelectFrame::Command_SelectFrame(const std::string& frameName)
	{
		Header = (U8)RVI_COMMAND_HEADER::SELECT_FRAME;
		FrameName = frameName;
	}

	Command_SelectFrame::Command_SelectFrame(std::string&& frameName)
	{
		Header = (U8)RVI_COMMAND_HEADER::SELECT_FRAME;
		FrameName = std::move(frameName);
	}

	void Command_SelectFrame::BuildData()
	{
		AppendData(Serializer::GetBytes(FrameName));
	}

	Command_DeleteFrame::Command_DeleteFrame(const std::string& frameName)
	{
		Header = (U8)RVI_COMMAND_HEADER::DELETE_FRAME;
		FrameName = frameName;
	}

	Command_DeleteFrame::Command_DeleteFrame(std::string&& frameName)
	{
		Header = (U8)RVI_COMMAND_HEADER::DELETE_FRAME;
		FrameName = std::move(frameName);
	}

	void Command_DeleteFrame::BuildData()
	{
		AppendData(Serializer::GetBytes(FrameName));
	}

	Command_ClearFrame::Command_ClearFrame(const std::string & frameName)
	{
		Header = (U8)RVI_COMMAND_HEADER::CLEAR_FRAME;
		FrameName = frameName;
	}

	Command_ClearFrame::Command_ClearFrame(std::string && frameName)
	{
		Header = (U8)RVI_COMMAND_HEADER::CLEAR_FRAME;
		FrameName = std::move(frameName);
	}

	void Command_ClearFrame::BuildData()
	{
		AppendData(Serializer::GetBytes(FrameName));
	}
}