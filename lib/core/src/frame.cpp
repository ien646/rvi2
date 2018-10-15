#include "frame.hpp"

#include <stack>

namespace rvi
{
    frame::frame(const std::string& name, frame* parent)
        : _name(name)
        , _transform(DEFAULT_TRANSFORM)
        , _parent(parent)
    { }

    frame::frame(std::string&& name, frame* parent)
        : _name(std::move(name))
        , _transform(DEFAULT_TRANSFORM)
        , _parent(parent)
    { }

    bool frame::has_parent() const noexcept
    {
        return _parent != nullptr;
    }

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
            _childs.push_back(std::make_unique<frame>(name, this));
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
        _cached_absolute_transform_needs_rebuild = true;
    }

    void frame::set_transform(transform2&& tform) noexcept
    {
        _transform = std::move(tform);
        _cached_absolute_transform_needs_rebuild = true;
    }

    void frame::set_position(vector2 offset) noexcept
    {
        _transform.position = offset;
        _cached_absolute_transform_needs_rebuild = true;
    }

    void frame::set_rotation(float rotation) noexcept
    {
        _transform.rotation = rotation;
        _cached_absolute_transform_needs_rebuild = true;
    }

    void frame::set_scale(vector2 scale) noexcept
    {
        _transform.scale = scale;
        _cached_absolute_transform_needs_rebuild = true;
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

    frame* frame::parent() const noexcept
    {
        return _parent;
    }

    transform2 frame::get_absolute_transform() noexcept
    {
        if(_cached_absolute_transform_needs_rebuild)
        {
            std::stack<transform2> tform_stack;
            tform_stack.push(_transform);

            const frame* current = this;
            while(current->has_parent())
            {
                current = current->_parent;
                tform_stack.push(current->_transform);
            }

            _cached_absolute_transform = transform2::default_value();
            while(!tform_stack.empty())
            {
                transform2 tf = tform_stack.top();
                _cached_absolute_transform.merge_in_place(tf);
                tform_stack.pop();
            }
        }

        return _cached_absolute_transform;
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