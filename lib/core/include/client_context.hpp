#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <type_traits>

#include "rvi_base.hpp"
#include "frame.hpp"
#include "line.hpp"
#include "definition.hpp"

namespace rvi
{
    class client_context
    {
    private:
        const transform2 DEFAULT_TRANSFORM = transform2(vector2(0, 0), vector2(1, 1), 0);

        frame _main_frame;
        std::reference_wrapper<frame> _selected_frame;

        // Current frame selection 'stack'
        std::vector<std::reference_wrapper<frame>> _frame_stack;

        std::unordered_map<std::string, definition> _local_definitions;

        // Framepaths of altered frames since last full or partial snapshot
        std::unordered_set<std::string> _modified_fpaths;

        bool _cached_fpath_rebuild = true;
        std::string _cached_fpath = MAIN_FRAMENAME;

    public:
        static const std::string MAIN_FRAMENAME;
        static const char FRAMEPATH_SEPARATOR;

        client_context();

        void draw_line(vector2 from, vector2 to);
        void draw_line(vector2 from, color_rgba fromColor, vector2 to, color_rgba toColor);
        void draw_line(vertex from, vertex to);
        void draw_line(const line& ln);
        void draw_line(line&& ln);

        void select_frame(const std::string& name);
        void select_frame(std::string&& name);

        bool release_frame();

        bool delete_frame(const std::string& name);

        const frame& selected_frame() const noexcept;
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

        void add_definition(const definition& instruction);
        void add_definition(definition&& instruction);

        void delete_definition(const std::string& name);

        bool execute_definition(const std::string& defName);

        bool contains_definition(const std::string& defName);

        const std::string& get_fpath();
        const frame& find_frame(const std::string& fPath);
        const std::pair<frame&, transform2> find_frame_with_mod_tform(const std::string& fPath);

        void mark_frame_modified();

        std::vector<line> snapshot_full_flat() const;
        std::vector<line> snapshot_diff_flat();

        std::unordered_map<std::string, std::vector<line>> snapshot_diff_relative();        
    };
}