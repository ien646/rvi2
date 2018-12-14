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
    /**
     * @brief Represents the abstract UI context of a client.
     * Manages frame creation, lifetime, state, etc.
     */
    class client_context
    {
    private:
        const transform2 DEFAULT_TRANSFORM = transform2(vector2(0, 0), vector2(1, 1), 0);

        std::unique_ptr<frame> _main_frame;
        frame* _selected_frame;

        // Current frame selection 'stack'
        std::vector<frame*> _frame_stack;

        // Altered frames since last full or partial snapshot
        std::unordered_set<frame*> _modified_frames;

        color_rgba _current_color;

        std::vector<std::string> _deleted_frame_queue;

    public:
        ///Global main frame name
        static const std::string MAIN_FRAMENAME;

        ///Frame-path separator character
        static const char FRAMEPATH_SEPARATOR;

        ///Default constructor
        client_context();

        ///Default move constructor
        client_context(client_context&& mv_src) = default;

        ///Explicit copy constructor
        client_context create_shallow_copy();

        /**
         * @brief Construct and append a new line to the currently selected frame.
         * The color of the line vertices is set to the currently selected color.
         * 
         * @param from Start vertex position
         * @param to End vertex position
         */
        void draw_line(vector2 from, vector2 to);

        /**
         * @brief Construct and append a new line to the currently selected frame.
         * 
         * @param from Start position
         * @param fromColor Start vertex color
         * @param to End vertex position
         * @param toColor End vertex color
         */
        void draw_line(vector2 from, color_rgba from_color, vector2 to, color_rgba to_color);

        /**
         * @brief Construct and append a new line to the currently selected frame.
         * 
         * @param from Start vertex
         * @param to End vertex
         */
        void draw_line(vertex from, vertex to);

        /**
         * @brief Append a new line to the currently selected frame.
         * 
         * @param ln Line
         */
        void draw_line(const line& ln);

        /**
         * @brief Append a new line to the currently selected frame.
         * 
         * @param ln Line
         */
        void draw_line(line&& ln);

        /**
         * @brief Select a new frame by name. If the frame does not
         * exist within the selected frame's children, a new child
         * frame is created and selected.
         * 
         * @param name Child frame name
         * @return frame* Pointer to the newly selected frame
         */
        frame* select_frame(const std::string& name);

        /**
         * @brief Select a new frame by name. If the frame does not
         * exist within the selected frame's children, a new child
         * frame is created and selected.
         * 
         * @param name Child frame name
         * @return frame* Pointer to the newly selected frame
         */
        frame* select_frame(std::string&& name);

        /**
         * @brief Select a new frame by setting the frame pointer directly.
         * Intended for restoring a previously selected frame, or to
         * avoid name lookup within the current children map.
         * Selecting a frame not held by this client_context will
         * result in undefined behaviour and (very)possible data corruption.
         * 
         * @param fptr Previously selected 
         */
        void select_frame(frame* fptr);

        /**
         * @brief Releases the currently selected frame, selecting its
         * parent as the new selected frame.
         * If the selected frame is the main frame (has no parent),
         * no release operation is performed.
         * 
         * @return true Successfully released frame
         * @return false No release performed
         */
        bool release_frame();

        /**
         * @brief Deletes a frame from the currently selected frame's children.
         * 
         * @param name Child frame name
         * @return true Deletion succesful
         * @return false No deletion performed (child frame not found)
         */
        bool delete_frame(const std::string& name);

        /**
         * @brief Deletes all children held by the currently selected frame
         */
        void clear_children();

        /**
         * @brief Return pointer to the currently selected frame
         */
        frame* selected_frame() noexcept;

        /**
         * @brief Return current context color
         */
        color_rgba current_color() const noexcept;

        /**
         * @return true Selected frame is the root frame
         * @return false Selected frame is not the root frame
         */
        bool is_root_frame_selected() const noexcept;

        /**
         * @brief Set the context's currently selected color
         */
        void set_color(color_rgba color) noexcept;

        /**
         * @brief Set the currently selected frame's transform
         */
        void set_transform(const transform2& tform) noexcept;

        /**
         * @brief Set the currently selected frame's transform
         */
        void set_transform(transform2&& tform) noexcept;

        /*
         * @brief Set the currently selected frame's scale as
         * absolute (ignores parent scale)
         */
        void set_transform_scale_abs(bool enabled) noexcept;

        /**
         * @brief Get the currently selected frame's transform
         */
        const transform2& transform() const noexcept;        

        /**
         * @brief Set the currently selected frame's position
         */
        void set_position(vector2 offset) noexcept;

        /**
         * @brief Set the currently selected frame's rotation
         */
        void set_rotation(float rotation) noexcept;

        /**
         * @brief Set the currently selected frame's scale
         */
        void set_scale(vector2 scale) noexcept;

        /**
         * @brief Get the currently selected frame's position
         */
        vector2 position() const noexcept;

        /**
         * @brief Get the currently selected frame's rotation
         */
        float rotation() const noexcept;

        /**
         * @brief Get the currently selected frame's scale
         */
        vector2 scale() const noexcept;

        /**
         * @brief Get the count of all frames held by this context
         */
        size_t frame_count() const noexcept;

        /**
         * @brief Clear currently selected frame
         */
        void clear_frame() noexcept;

        /**
         * @brief Get the full frame name (path) for a frame.
         * 
         * @param fptr Pointer to the frame to get its full name from.
         * If (fptr == nullptr) -> Use currently selected frame
         * @return std::string Full frame name (path)
         */
        std::string get_full_frame_name(frame* fptr = nullptr) noexcept;

        /**
         * @brief Find a frame with the given full frame name (path)
         * 
         * @param fPath Full frame name
         * @return frame* Pointer to the found frame. nullptr if not found
         */
        frame* find_frame(const std::string& fPath);

        /**
         * @brief Mark currently selected frame as modified.
         */
        void mark_frame_modified();

        /**
         * @brief Generate a full, flattened snapshot of the context's
         * current state.
         * 
         * @return std::vector<line> Snapshot data
         */
        std::vector<line> snapshot_full_flat() const;

        /**
         * @brief Generate a full, frame-name-relative snapshot of the
         * context's current state.
         * 
         * @return relative_snapshot Snapshot data
         */
        relative_snapshot snapshot_full_relative();

        /**
         * @brief Generate a differential, frame-name-relative snapshot of the
         * context's current state, relative to the previous differential snapshot.
         * 
         * @return relative_snapshot 
         */
        relative_snapshot snapshot_diff_relative();

    private:
        void add_deleted_frames_to_snapshot(relative_snapshot& sh);
    };
}