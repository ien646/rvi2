/* FILE: frame.h */
#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

#include "line.h"
#include "transform2.h"
#include "colorRgba.h"

namespace rvi
{
    class Frame
    {
    private:
        std::string _name;
        std::vector<Line> _lines;
        std::unordered_map<std::string, Frame&> _childFramesMap;
        std::vector<Frame> _childFrames;
        Transform2 _transform;
        ColorRGBA _color;

    public:
        Frame() = delete;

        Frame(const std::string& name);
        Frame(std::string&& name);

        void ClearLines() noexcept;

        void AddLine(const Line& ln);
        void AddLine(Line&& ln);

        void AddChildFrame(const std::string& name);
        void AddChildFrame(std::string&& name);

        void GetModulatedLines(std::vector<Line>& result, const Transform2& parentTform);

        // -- Getters --
        const std::string& Name() const noexcept;
        const std::vector<Line>& Lines() const noexcept;
        const std::vector<Frame>& Frames() const noexcept;
        const Transform2& Transform() const noexcept;
        ColorRGBA Color() const noexcept;
        Frame& GetChildFrame(const std::string& name);

        // -- Setters --
        void SetColor(U8 r, U8 g, U8 b, U8 a) noexcept;
        void SetColor(ColorRGBA color) noexcept;
        void SetTransform(const Transform2& tform) noexcept;
        void SetTransform(Transform2&& tform) noexcept;
    };
}