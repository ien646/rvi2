#pragma once

#include <string>
#include <stack>
#include <unordered_map>

#include "rvi_base.h"
#include "frame.h"
#include "line.h"
#include "definition.h"

namespace rvi
{
    class ClientContext
    {
    private:
        const std::string MAIN_FRAMENAME = "__MAINFRAME__";

        Frame _mainFrame;
        Frame& _selectedFrame;
        std::stack<std::reference_wrapper<Frame>> _frameStack;
        U64 _contextId;
        std::unordered_map<std::string, Definition> _localDefinitions;

    public:
        ClientContext() noexcept;

        U64 ContextId() const;

        void DrawLine(Vector2 from, Vector2 to);
        void DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor);
        void DrawLine(Vertex from, Vertex to);

        void SelectFrame(const std::string& name);
        void SelectFrame(std::string&& name);

        void ReleaseFrame();

        void SetCurrentColor(ColorRGBA color);

        void SetCurrentTransform(const Transform2& tform);
        void SetCurrentTransform(Transform2&& tform);

        const Transform2& GetCurrentTransform() const;

        void SetCurrentOffset(Vector2 offset);
        void SetCurrentRotation(float rotation);
        void SetCurrentScale(Vector2 scale);

        Vector2 GetCurrentOffset() const;
        float GetCurrentRotation() const;
        Vector2 GetCurrentScale() const;

        void ClearFrame();

        void AddDefinition(const std::string& name, const Definition& instruction);
        void AddDefinition(std::string&& name, const Definition& instruction);
        void AddDefinition(const std::string& name, Definition&& instruction);
        void AddDefinition(std::string&& name, Definition&& instruction);
    };
}