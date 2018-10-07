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

    frame* frame::add_child(const std::string& name)
    {
        if (_child_frames_index.count(name) > 0)
        {
            return _child_frames_index.at(name);
        }
        else
        {
            _childs.push_back(std::make_unique<frame>(name));
            frame* f_ptr = _childs.back().get();
            _child_frames_index.emplace(name, f_ptr);
            return f_ptr;
        }
    }

    bool frame::delete_child(const std::string& name)
    {
        if (_child_frames_index.count(name) == 0)
        {
            return false;
        }
        
        frame* f_ptr = _child_frames_index.at(name);

        auto it = std::find_if(_childs.begin(), _childs.end(), [&](auto& fuptr)
        {
            return fuptr.get() == f_ptr;
        });

        _childs.erase(it);
        _child_frames_index.erase(name);
        
        return true;
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
        for (auto& entry : _child_frames_index)
        {            
            const frame* f_ptr = entry.second;
            std::vector<line> child_lines = f_ptr->get_all_modulated_lines(abs_tform);
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
        return (_child_frames_index.count(name) > 0);
    }

    size_t frame::child_count(bool deep) const noexcept
    {
        if (!deep)
        {
            return _child_frames_index.size();
        }
        else
        {
            size_t result = 0;
            for (const auto& f : _child_frames_index)
            {
                result++;           
                result += _child_frames_index.at(f.first)->child_count(true);
            }
            return result;
        }
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

    std::unordered_map<std::string, frame*> frame::children() const noexcept
    {
        std::unordered_map<std::string, frame*> result;

        for (auto& p : _child_frames_index)
        {
            std::string name = p.first;
            frame* f_ptr = _child_frames_index.at(name);
            result.emplace(std::move(name), f_ptr);
        }

        return result;
    }

    const transform2& frame::transform() const noexcept
    {
        return _transform;
    }

    frame* frame::get_child(const std::string& name)
    {
        return _child_frames_index.at(name);
    }

    size_t frame::line_count() const noexcept
    {
        return _lines.size();
    }
}