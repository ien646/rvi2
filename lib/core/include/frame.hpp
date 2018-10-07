#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <memory>

#include "line.hpp"
#include "transform2.hpp"
#include "color_rgba.hpp"

namespace rvi
{
    class frame
    {
    private:
        const transform2 DEFAULT_TRANSFORM = transform2(vector2(0, 0), vector2(1, 1), 0);

        std::string _name;
        std::vector<line> _lines;
        std::vector<std::unique_ptr<frame>> _childs;
        std::unordered_map<std::string, frame*> _child_frames_index;
        transform2 _transform;
        
    public:
        frame() = delete;
        frame(const frame&) = delete;

        frame(frame&& mv_src) = default;

        frame(const std::string& name);
        frame(std::string&& name);

        void clear_lines() noexcept;

        size_t line_count() const noexcept;

        void add_line(const line& ln);
        void add_line(line&& ln);

        frame* add_child(const std::string& name);

        bool delete_child(const std::string& name);

        std::vector<line> get_all_modulated_lines(const transform2& parent_tform) const;
        std::vector<line> get_manually_modulated_lines(const transform2& parent_tform) const;

        bool contains_child(const std::string& name);

        size_t child_count(bool deep = false) const noexcept;

        // -- Getters --
        const std::string& name() const noexcept;
        const std::vector<line>& lines() const noexcept;
        std::unordered_map<std::string, frame*> children() const noexcept;
        const transform2& transform() const noexcept;
        frame* get_child(const std::string& name);

        // -- Setters --
        void set_transform(const transform2& tform) noexcept;
        void set_transform(transform2&& tform) noexcept;
        void set_position(vector2 offset) noexcept;
        void set_rotation(float rotation) noexcept;
        void set_scale(vector2 scale) noexcept;
    };
}