#include "client_context.hpp"

#include <sstream>
#include <iterator>

namespace rvi
{ 
    const char client_context::FRAMEPATH_SEPARATOR = ':';
    const std::string client_context::MAIN_FRAMENAME = "__MAINFRAME__";

    #if RVI_COMPILER_MSVC
    #pragma warning(suppress: 26439)
    #endif
    client_context::client_context()
        : _main_frame(MAIN_FRAMENAME)
        , _selected_frame(_main_frame)
    {
        _frame_stack.push_back(_main_frame);
    }

    void client_context::draw_line(vector2 from, vector2 to)
    {
        line ln(vertex(from, _selected_frame.get().color()),
                vertex(to,  _selected_frame.get().color()));

        _selected_frame.get().add_line(std::move(ln));
        mark_frame_modified();
    }

    void client_context::draw_line(vector2 from, color_rgba from_color, vector2 to, color_rgba to_color)
    {
        _selected_frame.get().add_line(line(vertex(from, from_color), vertex(to, to_color)));
        mark_frame_modified();
    }

    void client_context::draw_line(vertex from, vertex to)
    {        
        _selected_frame.get().add_line(line(from, to));
        mark_frame_modified();
    }

    void client_context::draw_line(line&& ln)
    {
        _selected_frame.get().add_line(std::move(ln));
    }

    void client_context::select_frame(const std::string& name)
    {
        if (!_selected_frame.get().contains_child(name))
        {
            _selected_frame = _selected_frame.get().add_child(name);
        }
        else
        {
            _selected_frame = _selected_frame.get().get_child(name);
        }
        _frame_stack.push_back(_selected_frame);
        _cached_fpath_rebuild = true;
    }

    void client_context::select_frame(std::string&& name)
    {
        if (!_selected_frame.get().contains_child(name))
        {
            _selected_frame = _selected_frame.get().add_child(std::move(name));
        }
        else
        {
            _selected_frame = _selected_frame.get().get_child(name);
        }
        _frame_stack.push_back(_selected_frame);
        _cached_fpath_rebuild = true;
    }

    bool client_context::release_frame()
    {
        if (&_selected_frame.get() == &_main_frame)
        {
            return false;
        }
        _cached_fpath_rebuild = true;
        _frame_stack.pop_back();
        _selected_frame = _frame_stack.back();
        return true;
    }

    bool client_context::delete_frame(const std::string& name)
    {
        return _selected_frame.get().delete_child(name);
    }

    const rvi::frame& client_context::selected_frame() const noexcept
    {
        return _selected_frame;
    }

    bool client_context::is_root_frame_selected() const noexcept
    {
        return &_main_frame == &_selected_frame.get();
    }

    void client_context::set_color(color_rgba color) noexcept
    {
        _selected_frame.get().set_color(color);
    }

    void client_context::set_transform(const transform2& tform) noexcept
    {
        _selected_frame.get().set_transform(tform);
    }

    void client_context::set_transform(transform2&& tform) noexcept
    {
        _selected_frame.get().set_transform(std::move(tform));
    }

    const transform2& client_context::transform() const noexcept
    {
        return _selected_frame.get().transform();
    }

    void client_context::set_position(vector2 offset) noexcept
    {
        _selected_frame.get().set_position(offset);
    }

    void client_context::set_rotation(float rotation) noexcept
    {
        _selected_frame.get().set_rotation(rotation);
    }

    void client_context::set_scale(vector2 scale) noexcept
    {
        _selected_frame.get().set_scale(scale);
    }

    vector2 client_context::position() const noexcept
    {
        return _selected_frame.get().transform().position;
    }

    float client_context::rotation() const noexcept
    {
        return _selected_frame.get().transform().rotation;
    }

    vector2 client_context::scale() const noexcept
    {
        return _selected_frame.get().transform().scale;
    }

    size_t client_context::frame_count() const noexcept
    {
        size_t result = 1;
        result += _main_frame.child_count(true);
        return result;
    }

    void client_context::clear_frame() noexcept
    {
        _selected_frame.get().clear_lines();
        mark_frame_modified();
    }

    void client_context::add_definition(const definition& instruction)
    {
        DISCARD_RESULT _local_definitions.emplace(instruction.name(), instruction);
    }

    void client_context::add_definition(definition&& instruction)
    {
        auto name = instruction.name();
        DISCARD_RESULT _local_definitions.emplace(name, instruction);
    }    

    void client_context::delete_definition(const std::string& name)
    {
        _local_definitions.erase(name);
    }

    bool client_context::execute_definition(const std::string& def_name)
    {
        if (_local_definitions.count(def_name) == 0)
        {
            return false;
        }
        definition def = _local_definitions.at(def_name);
        def.execute_on_context(*this);
        return true;
    }

    bool client_context::contains_definition(const std::string& def_name)
    {
        return _local_definitions.count(def_name) > 0;
    }

    const std::string& client_context::get_fpath()
    {
        static const std::string separator = std::string(1, FRAMEPATH_SEPARATOR);

        if (_cached_fpath_rebuild)
        {
            _cached_fpath.clear();
            _cached_fpath = _frame_stack[0].get().name();
            for (size_t i = 1; i < _frame_stack.size(); i++)
            {
                _cached_fpath.append(separator);
                _cached_fpath.append(_frame_stack[i].get().name());
            }
            _cached_fpath_rebuild = false;
        }
        return _cached_fpath;
    }

    const std::pair<transform2, frame&> client_context::extract_fpath_with_transform(const std::string& fpath)
    {
        std::stringstream ss(fpath);
        std::string aux;
        frame* currentFrame = nullptr;
        transform2 currentTransform;

        currentFrame = &_main_frame;
        currentTransform = currentFrame->transform();

        while (std::getline(ss, aux, FRAMEPATH_SEPARATOR))
        {
            if (aux != MAIN_FRAMENAME)
            {
                currentFrame = &currentFrame->get_child(aux);
                currentTransform.merge_in_place(currentFrame->transform());
            }
        }
        return std::pair<transform2, frame&>(currentTransform, *currentFrame);
    }

    void client_context::mark_frame_modified()
    {
        const std::string& fpath = get_fpath();
        if (_modified_fpaths.count(fpath) == 0)
        {
            DISCARD_RESULT _modified_fpaths.insert(fpath);
        }
    }

    std::vector<line> client_context::snapshot_full_flat() const
    {
        return _main_frame.get_flat_modulated_lines(DEFAULT_TRANSFORM);
    }

    std::vector<line> client_context::snapshot_diff_flat()
    {
        std::vector<line> result;
        for (auto& fpath : _modified_fpaths)
        {
            const auto pair = extract_fpath_with_transform(fpath);
            const transform2 parentTform = pair.first;
            const frame& frame = pair.second;

            std::vector<line> lines = frame.get_flat_modulated_lines(parentTform);
            std::move(lines.begin(), lines.end(), std::back_inserter(result));
        }
        _modified_fpaths.clear();
        return result;
    }

    std::unordered_map<std::string, std::vector<line>> client_context::snapshot_diff_relative()
    {
        std::unordered_map<std::string, std::vector<line>> result;
        for (auto& fpath : _modified_fpaths)
        {
            const auto pair = extract_fpath_with_transform(fpath);
            const transform2 parentTform = pair.first;
            const frame& frame = pair.second;

            auto entry = std::make_pair(fpath, frame.get_flat_modulated_lines(parentTform));
            result.insert(std::move(entry));
        }
        _modified_fpaths.clear();
        return result;
    }
}