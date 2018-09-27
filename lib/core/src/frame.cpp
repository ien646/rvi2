#include "frame.hpp"

namespace rvi
{
    frame::frame(const std::string& name)
        : _name(name)
        , _transform(DEFAULT_TRANSFORM)
    { }

    frame::frame(std::string&& name)
        : _name(std::move(name))
        , _transform(DEFAULT_TRANSFORM)
    { }

    void frame::clear_lines() noexcept
    {
        _lines.clear();
    }

    void frame::add_line(const line& ln)
    {
        _lines.push_back(ln);
    }

    void frame::add_line(line&& ln)
    {
        _lines.push_back(std::move(ln));
    }

    frame& frame::add_child(const std::string& name)
    {
        if(_child_frames.count(name) > 0)
        {
            return *_child_frames.at(name);
        }
        auto pair = _child_frames.emplace(name, std::make_unique<frame>(name));
        return *(pair.first->second);
    }

    frame& frame::add_child(std::string&& name)
    {
        if(_child_frames.count(name) > 0)
        {
            return *_child_frames.at(name);
        }
        std::string nameCopy = name;
        auto pair = _child_frames.emplace(nameCopy, std::make_unique<frame>(name));
        return *(pair.first->second);
    }

    bool frame::delete_child(const std::string& name)
    {
        return (_child_frames.erase(name) < 0);
    }

    std::vector<line> frame::get_all_modulated_lines(const transform2& parent_tform) const
    {
        std::vector<line> result;

        // Current absolute transform
        const transform2 abs_tform = _transform.merge(parent_tform);

        // Owned lines
        std::vector<line> own_lines = _lines;

        std::for_each(own_lines.begin(), own_lines.end(), 
            [&](line& line){ line.apply_transform(abs_tform); });
            
        std::move(own_lines.begin(), own_lines.end(), std::back_inserter(result));

        // Child frames
        for (auto& entry : _child_frames)
        {
            std::vector<line> child_lines = entry.second->get_all_modulated_lines(abs_tform);
            std::move(child_lines.begin(), child_lines.end(), std::back_inserter(result));
        }

        return result;
    }

    std::vector<line> frame::get_manually_modulated_lines(const transform2& parent_tform) const
    {
        std::vector<line> result;

        std::vector<line> ownLines = _lines;
        std::for_each(ownLines.begin(), ownLines.end(), 
            [&](line& line){ line.apply_transform(parent_tform); });
        std::move(ownLines.begin(), ownLines.end(), std::back_inserter(result));

        return result;
    }

    bool frame::contains_child(const std::string& name)
    {
        return (_child_frames.count(name) > 0);
    }

    size_t frame::child_count(bool deep) const noexcept
    {
        if (!deep)
        {
            return _child_frames.size();
        }
        else
        {
            size_t result = 0;
            for (const auto& f : _child_frames)
            {
                result++;
                result += f.second->child_count(true);
            }
            return result;
        }
    }

    void frame::set_color(u8 r, u8 g, u8 b, u8 a) noexcept
    {
        _color = color_rgba(r, g, b, a);
    }

    void frame::set_color(color_rgba color) noexcept
    {
        _color = color;
    }

    void frame::set_transform(const transform2& tform) noexcept
    {
        _transform = tform;
    }

    void frame::set_transform(transform2&& tform) noexcept
    {
        _transform = std::move(tform);
    }

    void frame::set_position(vector2 offset) noexcept
    {
        _transform.position = offset;
    }

    void frame::set_rotation(float rotation) noexcept
    {
        _transform.rotation = rotation;
    }

    void frame::set_scale(vector2 scale) noexcept
    {
        _transform.scale = scale;
    }

    const std::string& frame::name() const noexcept
    {
        return _name;
    }

    const std::vector<line>& frame::lines() const noexcept
    {
        return _lines;
    }

    const std::unordered_map<std::string, std::unique_ptr<frame>>& frame::children() const noexcept
    {
        return _child_frames;
    }

    const transform2& frame::transform() const noexcept
    {
        return _transform;
    }

    color_rgba frame::color() const noexcept
    {
        return _color;
    }

    frame& frame::get_child(const std::string& name) const
    {
        return *_child_frames.at(name);
    }

    size_t frame::line_count() const noexcept
    {
        return _lines.size();
    }
}