#include "client_context.hpp"

#include <stack>
#include <sstream>
#include <iterator>
#include <queue>

namespace rvi
{ 
    const char client_context::FRAMEPATH_SEPARATOR = ':';
    const std::string client_context::MAIN_FRAMENAME = "__MAINFRAME__";

    #if RVI_COMPILER_MSVC
    #pragma warning(suppress: 26439)
    #endif
    client_context::client_context()
    {
        _main_frame = std::make_unique<frame>(MAIN_FRAMENAME);
        _frame_stack.push_back(_main_frame.get());
        _selected_frame = _main_frame.get();
    }

    client_context client_context::create_shallow_copy()
    {
        client_context result;
        result._main_frame = _main_frame->create_copy(nullptr);
        result._selected_frame = _main_frame.get();
        result._frame_stack.clear();
        result._frame_stack.push_back(_main_frame.get());
        result._modified_frames.clear();
        result._modified_frames.emplace(_main_frame.get());
        result._cached_full_fnames.clear();
        result._current_color = _current_color;
        return result;
    }

    void client_context::draw_line(vector2 from, vector2 to)
    {
        line ln(vertex(from, _current_color),
                vertex(to, _current_color));

        _selected_frame->add_line(std::move(ln));
        mark_frame_modified();
    }

    void client_context::draw_line(vector2 from, color_rgba from_color, vector2 to, color_rgba to_color)
    {
        _selected_frame->add_line(line(vertex(from, from_color), vertex(to, to_color)));
        mark_frame_modified();
    }

    void client_context::draw_line(vertex from, vertex to)
    {        
        _selected_frame->add_line(line(from, to));
        mark_frame_modified();
    }

    void client_context::draw_line(line&& ln)
    {
        _selected_frame->add_line(std::move(ln));
        mark_frame_modified();
    }

    void client_context::draw_line(const line& ln)
    {
        _selected_frame->add_line(ln);
        mark_frame_modified();
    }

    void client_context::select_frame(const std::string& name)
    {
        if (!_selected_frame->contains_child(name))
        {
            _selected_frame = _selected_frame->add_child(name);
        }
        else
        {
            _selected_frame = _selected_frame->get_child(name);
        }
        _frame_stack.push_back(_selected_frame);
    }

    void client_context::select_frame(std::string&& name)
    {
        if (!_selected_frame->contains_child(name))
        {
            _selected_frame = _selected_frame->add_child(std::move(name));
        }
        else
        {
            _selected_frame = _selected_frame->get_child(name);
        }
        _frame_stack.push_back(_selected_frame);
    }

    bool client_context::release_frame()
    {
        if (_selected_frame == _main_frame.get())
        {
            return false;
        }
        _frame_stack.pop_back();
        _selected_frame = _frame_stack.back();
        return true;
    }

    bool client_context::delete_frame(const std::string& name)
    {
        _deleted_frame_queue.push_back(name);
        return _selected_frame->delete_child(name);
    }

    frame* client_context::selected_frame() noexcept
    {
        return _selected_frame;
    }

    bool client_context::is_root_frame_selected() const noexcept
    {
        return _main_frame.get() == _selected_frame;
    }

    void client_context::set_color(color_rgba color) noexcept
    {
        _current_color = color;
    }

    void client_context::set_transform(const transform2& tform) noexcept
    {
        _selected_frame->set_transform(tform);
        mark_frame_modified();
    }

    void client_context::set_transform(transform2&& tform) noexcept
    {
        _selected_frame->set_transform(std::move(tform));
        mark_frame_modified();
    }

    const transform2& client_context::transform() const noexcept
    {
        return _selected_frame->transform();
    }

    void client_context::set_position(vector2 offset) noexcept
    {
        _selected_frame->set_position(offset);
        mark_frame_modified();
    }

    void client_context::set_rotation(float rotation) noexcept
    {
        _selected_frame->set_rotation(rotation);
        mark_frame_modified();
    }

    void client_context::set_scale(vector2 scale) noexcept
    {
        _selected_frame->set_scale(scale);
        mark_frame_modified();
    }

    vector2 client_context::position() const noexcept
    {
        return _selected_frame->transform().position;
    }

    float client_context::rotation() const noexcept
    {
        return _selected_frame->transform().rotation;
    }

    vector2 client_context::scale() const noexcept
    {
        return _selected_frame->transform().scale;
    }

    size_t client_context::frame_count() const noexcept
    {
        size_t result = 1;
        result += _main_frame->child_count(true);
        return result;
    }

    void client_context::clear_frame() noexcept
    {
        _selected_frame->clear_lines();
        mark_frame_modified();
    }    

    std::string client_context::get_full_frame_name(frame* fptr) noexcept
    {
        if(fptr == nullptr)
        {
            fptr = _selected_frame;
        }

        if(_cached_full_fnames.count(fptr) > 0)
        {
            return _cached_full_fnames.at(fptr);
        }

        std::stack<frame*> frame_stack;
        frame* cur_ptr = fptr;
        frame_stack.push(cur_ptr);
        while(cur_ptr->has_parent())
        {
            cur_ptr = cur_ptr->parent();
            frame_stack.push(cur_ptr);
        }

        std::stringstream result;
        result << frame_stack.top()->name();
        frame_stack.pop();
        while(!frame_stack.empty())
        {
            result << FRAMEPATH_SEPARATOR << frame_stack.top()->name();
            frame_stack.pop();
        }

        std::string fname = result.str();
        _cached_full_fnames.emplace(fptr, fname);
        return fname;
    }

    frame* client_context::find_frame(const std::string& fpath)
    {
        std::stringstream ss(fpath);
        std::string aux;
        frame* currentFrame = nullptr;
        transform2 currentTransform;

        currentFrame = _main_frame.get();

        while (std::getline(ss, aux, FRAMEPATH_SEPARATOR))
        {
            if (aux != MAIN_FRAMENAME)
            {
                currentFrame = currentFrame->get_child(aux);
            }
        }
        return currentFrame;
    }

    void client_context::mark_frame_modified()
    {
        _modified_frames.insert(_selected_frame);
    }

    std::vector<line> client_context::snapshot_full_flat() const
    {
        std::vector<line> result;
        std::queue<frame*> remaining_frames;

        // Initial set consists of the main frame (== all frames)
        remaining_frames.push(_main_frame.get());        

        // Iterate all frames, while procedurally adding children
        while(!remaining_frames.empty())
        {
            frame* fptr = remaining_frames.front();
            for(auto& ch_pair : fptr->children())
            {
                remaining_frames.push(ch_pair.second);
            }

            auto& lines = fptr->lines();
            result.reserve(lines.size());
            
            for(line ln : lines) // expl. copy
            {
                ln.apply_transform(fptr->get_absolute_transform());
                result.push_back(ln);
            }

            remaining_frames.pop();
        }

        return result;
    }    

    relative_snapshot client_context::snapshot_full_relative()
    {
        relative_snapshot result;        

        std::queue<frame*> remaining_frames;
        remaining_frames.push(_main_frame.get());

        // Iterate all frames, while procedurally adding children
        while(!remaining_frames.empty())
        {
            frame* fptr = remaining_frames.front();
            for(auto& ch_pair : fptr->children())
            {
                remaining_frames.push(ch_pair.second);
            }

            auto& lines = fptr->lines();
            
            std::vector<line> entry_lines;
            entry_lines.reserve(lines.size());
            
            for(line ln : lines) // expl. copy
            {
                ln.apply_transform(fptr->get_absolute_transform());
                entry_lines.push_back(ln);
            }

            relative_snapshot_entry entry;
            entry.name = get_full_frame_name(fptr);
            entry.lines = std::move(entry_lines);
            entry.deleted = false;

            result.entries.push_back(std::move(entry));

            remaining_frames.pop();
        }

        return result;
    }

    relative_snapshot client_context::snapshot_diff_relative()
    {
        relative_snapshot result;

        add_deleted_frames_to_snapshot(result);

        std::queue<frame*> remaining_frames;
        
        for(frame* fptr : _modified_frames)
        {
            remaining_frames.push(fptr);
            for(auto& ch_pair : fptr->children())
            {
                remaining_frames.push(ch_pair.second);
            }
        }

        _modified_frames.clear();

        while(!remaining_frames.empty())
        {
            frame* fptr = remaining_frames.front();
            for(auto& ch_pair : fptr->children())
            {
                remaining_frames.push(ch_pair.second);
            }

            auto& lines = fptr->lines();
            
            std::vector<line> entry_lines;
            entry_lines.reserve(lines.size());
            
            for(line ln : lines) // expl. copy
            {
                ln.apply_transform(fptr->get_absolute_transform());
                entry_lines.push_back(ln);
            }

            relative_snapshot_entry entry;
            entry.name = get_full_frame_name(fptr);
            entry.lines = std::move(entry_lines);
            entry.deleted = false;

            result.entries.push_back(std::move(entry));

            remaining_frames.pop();
        }

        return result;
    }

    void client_context::add_deleted_frames_to_snapshot(relative_snapshot& sh)
    {
        // Enqueue deleted frames
        for(auto& deleted_frame : _deleted_frame_queue)
        {
            relative_snapshot_entry entry;
            entry.deleted = true;
            sh.entries.push_back(std::move(entry));
        }
        _deleted_frame_queue.clear();
    }
}