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
        const Transform2 DEFAULT_TRANSFORM = Transform2(Vector2(0, 0), Vector2(1, 1), 0);

        Frame _mainFrame;
        std::reference_wrapper<Frame> _selectedFrame;
        std::stack<std::reference_wrapper<Frame>> _frameStack;
        U64 _contextId;
        std::unordered_map<std::string, Definition> _localDefinitions;

		ClientContext();
    public:
		static ClientContext CreateNew();

        U64 ContextId() const noexcept;

        void DrawLine(Vector2 from, Vector2 to);
        void DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor);
        void DrawLine(Vertex from, Vertex to);

        void SelectFrame(const std::string& name);
        void SelectFrame(std::string&& name);

        bool ReleaseFrame();

        bool DeleteFrame(const std::string& name);

        void SetCurrentColor(ColorRGBA color) noexcept;

        void SetCurrentTransform(const Transform2& tform) noexcept;
        void SetCurrentTransform(Transform2&& tform) noexcept;

        const Transform2& GetCurrentTransform() const noexcept;

        void SetCurrentOffset(Vector2 offset) noexcept;
        void SetCurrentRotation(float rotation) noexcept;
        void SetCurrentScale(Vector2 scale) noexcept;

        Vector2 GetCurrentOffset() const noexcept;
        float GetCurrentRotation() const noexcept;
        Vector2 GetCurrentScale() const noexcept;

        void ClearFrame() noexcept;

        void AddDefinition(const std::string& name, const Definition& instruction);
        void AddDefinition(std::string&& name, const Definition& instruction);
        void AddDefinition(const std::string& name, Definition&& instruction);
        void AddDefinition(std::string&& name, Definition&& instruction);

        std::vector<Line> GetSnapshot();
    };
}