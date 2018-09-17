/* FILE: frame.h */
#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

#include "line.h"
#include "transform2.h"
#include "color_rgba.h"

namespace rvi
{
    class Frame
    {
    private:
        const Transform2 DEFAULT_TRANSFORM = Transform2(Vector2(0, 0), Vector2(1, 1), 0);

        std::string _name;
        std::vector<Line> _lines;
        std::unordered_map<std::string, Frame> _childFrames;
        Transform2 _transform;
        ColorRGBA _color;

    public:
        Frame() = delete;

        Frame(const std::string& name);
        Frame(std::string&& name);

        void ClearLines() noexcept;

        void AddLine(const Line& ln);
        void AddLine(Line&& ln);

        void AddLine(const Vertex& from, const Vertex& to);
        void AddLine(Vertex&& from, Vertex&& to);

        Frame& AddChildFrame(const std::string& name);
        Frame& AddChildFrame(std::string&& name);
        
        bool DeleteChildFrame(const std::string& name);

        std::vector<Line> GetModulatedLines(const Transform2& parentTform);

        bool ContainsChildFrame(const std::string& name);

        // -- Getters --
        const std::string& Name() const noexcept;
        const std::vector<Line>& Lines() const noexcept;
        const std::unordered_map<std::string, Frame>& Frame::Frames() const noexcept;
        const Transform2& Transform() const noexcept;
        ColorRGBA Color() const noexcept;
        Frame& GetChildFrame(const std::string& name);
        size_t LineCount() const noexcept;

        // -- Setters --
        void SetColor(U8 r, U8 g, U8 b, U8 a) noexcept;
        void SetColor(ColorRGBA color) noexcept;
        void SetTransform(const Transform2& tform) noexcept;
        void SetTransform(Transform2&& tform) noexcept;
        void SetOffset(Vector2 offset) noexcept;
        void SetRotation(float rotation) noexcept;
        void SetScale(Vector2 scale) noexcept;

    private:
    };
}