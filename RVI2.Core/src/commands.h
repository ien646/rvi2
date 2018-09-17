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
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_RequestAck : public CommandBase
    {
    public:
        U16 RequestId = 0;

        Command_RequestAck() noexcept { }
        Command_RequestAck(U16 reqId) noexcept;

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_ResponseAck : public CommandBase
    {
    public:
        U16 RequestId = 0;

        Command_ResponseAck() noexcept { }
        Command_ResponseAck(U16 reqId) noexcept;

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_DrawLine : public CommandBase
    {
    public:
        Vertex VxFrom, VxTo;

        Command_DrawLine() noexcept { }
        Command_DrawLine(const Vertex& vxFrom, const Vertex& vxTo);
        Command_DrawLine(Vertex&& vxFrom, Vertex&& vxTo);

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_SelectFrame : public CommandBase
    {
    public:
        std::string FrameName;

        Command_SelectFrame() noexcept { }
        Command_SelectFrame(const std::string& frameName);
        Command_SelectFrame(std::string&& frameName);

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_DeleteFrame : public CommandBase
    {
    public:
        std::string FrameName;

        Command_DeleteFrame() noexcept { }
        Command_DeleteFrame(const std::string& frameName);
        Command_DeleteFrame(std::string&& frameName);

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_ClearFrame : public CommandBase
    {
    public:
        std::string FrameName;

        Command_ClearFrame() noexcept { }
        Command_ClearFrame(const std::string& frameName);
        Command_ClearFrame(std::string&& frameName);

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };

    //|-----------------------------------|
    class Command_SendClick : public CommandBase
    {
        Vector2 ClickPosition;

        Command_SendClick() noexcept { }
        Command_SendClick(Vector2 clickPos) noexcept
        {
            ClickPosition = clickPos;
        }

        virtual void BuildData() override;
        virtual void ConstructFromData(const std::vector<U8> data) override;
    };
}