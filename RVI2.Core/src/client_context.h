#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <type_traits>

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
        const char FRAMEPATH_SEPARATOR = ':';
        const Transform2 DEFAULT_TRANSFORM = Transform2(Vector2(0, 0), Vector2(1, 1), 0);

        Frame _mainFrame;
        std::reference_wrapper<Frame> _selectedFrame;

        // Current frame selection 'stack'
        std::vector<std::reference_wrapper<Frame>> _frameStack;

        std::unordered_map<std::string, Definition> _localDefinitions;

        // Framepaths of altered frames since last full or partial snapshot
        std::unordered_set<std::string> _modifiedFramePaths;

        bool _cachedFramePathNeedsRebuild = true;
        std::string _cachedFramePath = MAIN_FRAMENAME;

        ClientContext();
    public:
        static ClientContext CreateNew();

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

        void DeleteDefinition(const std::string& name);

        const std::string& GetCurrentFramePath();
        const std::pair<Transform2, Frame&> ClientContext::FramePathToFrameWithTransform(const std::string& fPath);

        void MarkFrameAsModified();

        std::vector<Line> GetFullSnapshot();
        std::vector<Line> GetPartialSnapshot();
    };
}