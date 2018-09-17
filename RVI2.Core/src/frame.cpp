#include "frame.h"

namespace rvi
{
    Frame::Frame(const std::string& name)
        : _name(name)
        , _transform(DEFAULT_TRANSFORM)
    { }

    Frame::Frame(std::string&& name)
        : _name(std::move(name))
        , _transform(DEFAULT_TRANSFORM)
    { }

    void Frame::ClearLines() noexcept
    {
        _lines.clear();
    }

    void Frame::AddLine(const Line& ln)
    {
        _lines.push_back(ln);
    }

    void Frame::AddLine(Line&& ln)
    {
        _lines.push_back(std::move(ln));
    }

    void Frame::AddLine(const Vertex& from, const Vertex& to)
    {
        _lines.push_back(Line(from, to));
    }

    void Frame::AddLine(Vertex&& from, Vertex&& to)
    {
        _lines.push_back(Line(std::move(from), std::move(to)));
    }

    Frame& Frame::AddChildFrame(const std::string& name)
    {
        auto& pair = _childFrames.emplace(name, Frame(name));
        return pair.first->second;
    }

    Frame& Frame::AddChildFrame(std::string&& name)
    {
        std::string nameCopy = name;
        auto& pair = _childFrames.emplace(nameCopy, Frame(std::move(name)));
        return pair.first->second;
    }

    void Frame::GetModulatedLines(std::vector<Line>& result, const Transform2& parentTform)
    {
        // Current absolute transform
        const Transform2 absTform = _transform.Merge(parentTform);

        // Owned lines
        std::vector<Line> ownLines;
        ownLines.reserve(_lines.size());
        absTform.ApplyTo(ownLines);
        std::move(ownLines.begin(), ownLines.end(), std::back_inserter(result));

        // Child frames
        for (auto& entry : _childFrames)
        {
            Frame& childFrame = entry.second;
            childFrame.GetModulatedLines(result, absTform);
        }
    }

    bool Frame::ContainsChildFrame(const std::string& name)
    {
        return (_childFrames.count(name) > 0);
    }

    void Frame::SetColor(U8 r, U8 g, U8 b, U8 a) noexcept
    {
        _color = ColorRGBA(r, g, b, a);
    }

    void Frame::SetColor(ColorRGBA color) noexcept
    {
        _color = color;
    }

    void Frame::SetTransform(const Transform2& tform) noexcept
    {
        _transform = tform;
    }

    void Frame::SetTransform(Transform2&& tform) noexcept
    {
        _transform = std::move(tform);
    }

    void Frame::SetOffset(Vector2 offset)
    {
        _transform.Position = offset;
    }

    void Frame::SetRotation(float rotation)
    {
        _transform.Rotation = rotation;
    }

    void Frame::SetScale(Vector2 scale)
    {
        _transform.Scale = scale;
    }

    const std::string& Frame::Name() const noexcept
    {
        return _name;
    }

    const std::vector<Line>& Frame::Lines() const noexcept
    {
        return _lines;
    }

    const std::unordered_map<std::string, Frame>& Frame::Frames() const noexcept
    {
        return _childFrames;
    }

    const Transform2& Frame::Transform() const noexcept
    {
        return _transform;
    }

    ColorRGBA Frame::Color() const noexcept
    {
        return _color;
    }

    Frame& Frame::GetChildFrame(const std::string& name)
    {
        return _childFrames.at(name);
    }
}