#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <type_traits>

#include "rvi_base.hpp"
#include "frame.hpp"
#include "line.hpp"
#include "relative_snapshot.hpp"

namespace rvi
{
    class client_context
    {
    private:
        const transform2 DEFAULT_TRANSFORM = transform2(vector2(0, 0), vector2(1, 1), 0);

        std::unique_ptr<frame> _main_frame;
        frame* _selected_frame;

        // Current frame selection 'stack'
        std::vector<frame*> _frame_stack;

        // Framepaths of altered frames since last full or partial snapshot
        std::unordered_set<frame*> _modified_frames;

        std::unordered_map<frame*, std::string> _cached_full_fnames;

        color_rgba _current_color;

        std::vector<std::string> _deleted_frame_queue;

    public:
        static const std::string MAIN_FRAMENAME;
        static const char FRAMEPATH_SEPARATOR;

        client_context();

        client_context(client_context&& mv_src) = default;

        client_context create_shallow_copy();

        void draw_line(vector2 from, vector2 to);
        void draw_line(vector2 from, color_rgba fromColor, vector2 to, color_rgba toColor);
        void draw_line(vertex from, vertex to);
        void draw_line(const line& ln);
        void draw_line(line&& ln);

        frame* select_frame(const std::string& name);
        frame* select_frame(std::string&& name);
        void select_frame(frame* fptr);

        bool release_frame();

        bool delete_frame(const std::string& name);

        frame* selected_frame() noexcept;
        bool is_root_frame_selected() const noexcept;

        void set_color(color_rgba color) noexcept;

        void set_transform(const transform2& tform) noexcept;
        void set_transform(transform2&& tform) noexcept;

        const transform2& transform() const noexcept;

        void set_position(vector2 offset) noexcept;
        void set_rotation(float rotation) noexcept;
        void set_scale(vector2 scale) noexcept;

        vector2 position() const noexcept;
        float rotation() const noexcept;
        vector2 scale() const noexcept;

        size_t frame_count() const noexcept;

        void clear_frame() noexcept;

        std::string get_full_frame_name(frame* fptr = nullptr) noexcept;

        frame* find_frame(const std::string& fPath);

        void mark_frame_modified();

        std::vector<line> snapshot_full_flat() const;

        relative_snapshot snapshot_full_relative();

        relative_snapshot snapshot_diff_relative();

    private:
        void add_deleted_frames_to_snapshot(relative_snapshot& sh);
    };
}