#include "frame.hpp"

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

    Frame& Frame::AddChildFrame(const std::string& name)
    {
        if(_childFrames.count(name) > 0)
        {
            return *_childFrames.at(name);
        }
        auto pair = _childFrames.emplace(name, std::unique_ptr<Frame>(new Frame(name)));
        return *pair.first->second;
    }

    Frame& Frame::AddChildFrame(std::string&& name)
    {
        if(_childFrames.count(name) > 0)
        {
            return *_childFrames.at(name);
        }
        std::string nameCopy = name;
        auto pair = _childFrames.emplace(nameCopy, std::unique_ptr<Frame>(new Frame(std::move(name))));
        return *pair.first->second;
    }

    bool Frame::DeleteChildFrame(const std::string& name)
    {
        return (_childFrames.erase(name) < 0);
    }

    std::vector<Line> Frame::GetFlattenedModulatedLines(const Transform2& parentTform) const
    {
        std::vector<Line> result;

        // Current absolute transform
        const Transform2 absTform = _transform.Merge(parentTform);

        // Owned lines
        std::vector<Line> ownLines = _lines;

        std::for_each(ownLines.begin(), ownLines.end(), 
            [&](Line& line){ line.ApplyTransform(absTform); });
            
        std::move(ownLines.begin(), ownLines.end(), std::back_inserter(result));

        // Child frames
        for (auto& entry : _childFrames)
        {
            const Frame& childFrame = *entry.second;
            std::vector<Line> childLines = childFrame.GetFlattenedModulatedLines(absTform);
            std::move(childLines.begin(), childLines.end(), std::back_inserter(result));
        }

        return result;
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

    void Frame::SetOffset(Vector2 offset) noexcept
    {
        _transform.Position = offset;
    }

    void Frame::SetRotation(float rotation) noexcept
    {
        _transform.Rotation = rotation;
    }

    void Frame::SetScale(Vector2 scale) noexcept
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

    const std::unordered_map<std::string, std::unique_ptr<Frame>>& Frame::Frames() const noexcept
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
        return *_childFrames.at(name);
    }
    size_t Frame::LineCount() const noexcept
    {
        return _lines.size();
    }
}