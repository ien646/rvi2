#pragma once

#include "rvi_base.h"
#include "command_headers.h"
#include "command_base.h"
#include "vertex.h"

namespace rvi
{
    //|-----------------------------------|
    class Command_Nop : public CommandBase
    {
    public:
        Command_Nop() noexcept;

        virtual void BuildData() override;
    };

    //|-----------------------------------|
    class Command_RequestAck : public CommandBase
    {
    public:
        U16 RequestId;

        Command_RequestAck() = delete;
        Command_RequestAck(U16 reqId);

        virtual void BuildData() override;
    };

    //|-----------------------------------|
    class Command_ResponseAck : public CommandBase
    {
    public:
        U16 RequestId;

        Command_ResponseAck() = delete;
        Command_ResponseAck(U16 reqId);

        virtual void BuildData() override;
    };

    //|-----------------------------------|
    class Command_DrawLine : public CommandBase
    {
    public:
        Vertex VxFrom, VxTo;

        Command_DrawLine() = delete;
        Command_DrawLine(const Vertex& vxFrom, const Vertex& vxTo);
        Command_DrawLine(Vertex&& vxFrom, Vertex&& vxTo);

        virtual void BuildData() override;
    };

    //|-----------------------------------|
    class Command_SelectFrame : public CommandBase
    {
    public:
        std::string FrameName;

        Command_SelectFrame() = delete;
        Command_SelectFrame(const std::string& frameName);
        Command_SelectFrame(std::string&& frameName);

        virtual void BuildData() override;
    };

    //|-----------------------------------|
    class Command_DeleteFrame : public CommandBase
    {
    public:
        std::string FrameName;

        Command_DeleteFrame() = delete;
        Command_DeleteFrame(const std::string& frameName);
        Command_DeleteFrame(std::string&& frameName);

        virtual void BuildData() override;
    };

    //|-----------------------------------|
    class Command_ClearFrame : public CommandBase
    {
    public:
        std::string FrameName;

        Command_ClearFrame() = delete;
        Command_ClearFrame(const std::string& frameName);
        Command_ClearFrame(std::string&& frameName);

        virtual void BuildData() override;
    };
}