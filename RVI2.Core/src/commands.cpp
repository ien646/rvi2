#include "commands.h"
#include "serialization.h"

namespace rvi
{
    Command_Nop::Command_Nop() noexcept
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::NOP);
    }

    void Command_Nop::BuildData()
    {
        return;
    }

    void Command_Nop::ConstructFromData(const std::vector<U8> data)
    {
        Header = data[0];
        Checksum = data[1];
    }

    Command_RequestAck::Command_RequestAck(U16 reqId) noexcept
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::REQUEST_ACK);
        RequestId = reqId;
    }

    void Command_RequestAck::BuildData()
    {
        Serializer::SerializeInteger(Data, RequestId);
    }

    void Command_RequestAck::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;

        Header      = Serializer::DeserializeInteger<U8>(data, currentOffset);
        RequestId   = Serializer::DeserializeInteger<U16>(data, currentOffset);
        Checksum    = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }

    Command_ResponseAck::Command_ResponseAck(U16 reqId) noexcept
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::RESPONSE_ACK);
        RequestId = reqId;
    }

    void Command_ResponseAck::BuildData()
    {
        Serializer::SerializeInteger(Data, RequestId);
    }

    void Command_ResponseAck::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;

        Header      = Serializer::DeserializeInteger<U8>(data, currentOffset);
        RequestId   = Serializer::DeserializeInteger<U16>(data, currentOffset);
        Checksum    = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }

    Command_DrawLine::Command_DrawLine(const Vertex& vxFrom, const Vertex& vxTo)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::DRAW_LINE);
        VxFrom = vxFrom;
        VxTo = vxTo;
    }

    Command_DrawLine::Command_DrawLine(Vertex&& vxFrom, Vertex&& vxTo)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::DRAW_LINE);
        VxFrom = std::move(vxFrom);
        VxTo = std::move(vxTo);
    }

    void Command_DrawLine::BuildData()
    {
        Serializer::SerializeVertex(Data, VxFrom);
        Serializer::SerializeVertex(Data, VxTo);
    }

    void Command_DrawLine::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;

        Header      = Serializer::DeserializeInteger<U8>(data, currentOffset);
        VxFrom      = Serializer::DeserializeVertex(data, currentOffset);
        VxTo        = Serializer::DeserializeVertex(data, currentOffset);
        Checksum    = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }

    Command_SelectFrame::Command_SelectFrame(const std::string& frameName)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::SELECT_FRAME);
        FrameName = frameName;
    }

    Command_SelectFrame::Command_SelectFrame(std::string&& frameName)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::SELECT_FRAME);
        FrameName = std::move(frameName);
    }

    void Command_SelectFrame::BuildData()
    {
        Serializer::SerializeString(Data, FrameName);
    }

    void Command_SelectFrame::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;
        Header      = Serializer::DeserializeInteger<U8>(data, currentOffset);
        FrameName   = Serializer::DeserializeString(data, currentOffset);
        Checksum    = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }

    Command_DeleteFrame::Command_DeleteFrame(const std::string& frameName)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::DELETE_FRAME);
        FrameName = frameName;
    }

    Command_DeleteFrame::Command_DeleteFrame(std::string&& frameName)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::DELETE_FRAME);
        FrameName = std::move(frameName);
    }

    void Command_DeleteFrame::BuildData()
    {
        Serializer::SerializeString(Data, FrameName);
    }

    void Command_DeleteFrame::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;
        Header = Serializer::DeserializeInteger<U8>(data, currentOffset);
        FrameName = Serializer::DeserializeString(data, currentOffset);
        Checksum = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }

    Command_ClearFrame::Command_ClearFrame(const std::string & frameName)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::CLEAR_FRAME);
        FrameName = frameName;
    }

    Command_ClearFrame::Command_ClearFrame(std::string && frameName)
    {
        Header = static_cast<U8>(RVI_COMMAND_HEADER::CLEAR_FRAME);
        FrameName = std::move(frameName);
    }

    void Command_ClearFrame::BuildData()
    {
        Serializer::SerializeString(Data, FrameName);
    }

    void Command_ClearFrame::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;
        Header = Serializer::DeserializeInteger<U8>(data, currentOffset);
        FrameName = Serializer::DeserializeString(data, currentOffset);
        Checksum = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }

    void Command_SendClick::BuildData()
    {
        Serializer::SerializeVector2(Data, ClickPosition);
    }

    void Command_SendClick::ConstructFromData(const std::vector<U8> data)
    {
        size_t currentOffset = 0;
        Header = Serializer::DeserializeInteger<U8>(data, currentOffset);
        ClickPosition = Serializer::DeserializeVector2(data, currentOffset);
        Checksum = Serializer::DeserializeInteger<U8>(data, currentOffset);
    }
}