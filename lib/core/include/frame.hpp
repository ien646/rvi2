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
    /**
     * @brief Line container. Supports various methods for drawing, transforming
     * and managing related data.
     */
    class frame
    {
    private:
        const transform2 DEFAULT_TRANSFORM = transform2(vector2(0, 0), vector2(1, 1), 0);

        std::string _name;
        std::vector<line> _lines;
        std::vector<std::unique_ptr<frame>> _children;
        std::unordered_map<std::string, frame*> _child_frames_index;
        frame* _parent = nullptr;

        transform2 _transform;
        bool _transform_scale_absolute = false;

        transform2 _cached_abs_tform;
        bool _cached_abs_tform_rebuild = true;
        
    public:
        frame() = delete;

        /**
         * Copy construction is disabled, as it can be quite heavy.
         * Use explicit create_copy method instead
         */
        frame(const frame&) = delete;

        ///Move constructor
        frame(frame&& mv_src) = default;

        ///Explicit copy constructor
        std::unique_ptr<frame> create_copy(frame* fptr_parent);

        /**
         * Construct a new frame object
         * 
         * @param name Frame name
         * @param parent Parent frame, nullptr in case of no parent
         */
        frame(const std::string& name, frame* parent = nullptr);

        /**
         * Construct a new frame object
         * 
         * @param name Frame name
         * @param parent Parent frame, nullptr in case of no parent
         */
        frame(std::string&& name, frame* parent = nullptr);

        ///Clear all lines contained by this frame 
        void clear_lines() noexcept;

        ///Total amount of lines contained by this frame
        size_t line_count() const noexcept;

        /**
         * Insert a new line
         * 
         * @param ln Line to be inserted
         */
        void add_line(const line& ln);

        /**
         * Insert a new line
         * 
         * @param ln Line to be inserted
         */
        void add_line(line&& ln);

        /**
         * Construct a new frame and append it to this frame.
         * If a child with the same name existed previously,
         * no frame is created.
         * 
         * @param name Child frame name
         * @return frame* Pointer to the appended child frame
         */
        frame* add_child(const std::string& name);

        ///Safely delete all children
        void clear_children();

        /**
         * Obtain this frame's transform, applying all parent
         * transform information before its own.
         * 
         * @return transform2 Absolute transform
         */
        transform2 get_absolute_transform();

        /**
         * Attempt to delete a child frame
         * 
         * @param name Child frame name
         * @return true Deletion succesful
         * @return false No deletion performed
         */
        bool delete_child(const std::string& name);

        /**
         * Query if a child frame with the given name exists
         * 
         * @param name Child frame name
         */
        bool contains_child(const std::string& name);

        ///Query if this frame has a parent frame
        bool has_parent() const noexcept;

        /**
         * Query child frame count
         * 
         * @param deep Recursive query
         */
        size_t child_count(bool deep = false) const;

        // ------------ GETTERS ------------

        ///Get frame name
        const std::string& name() const noexcept;

        ///Get contained lines
        const std::vector<line>& lines() const noexcept;

        ///Get child frames
        std::unordered_map<std::string, frame*> children() const;

        ///Get relative frame transform
        const transform2& transform() const noexcept;

        /*
         * @brief Return absolute scale flag value
         */
        bool transform_scale_abs();

        /**
         * @brief Query for a child frame pointer
         * 
         * @param name Child frame name
         * @return frame* Child frame pointer, nullptr if not found
         */
        frame* get_child(const std::string& name);

        ///Parent frame
        frame* parent() const noexcept;

        // ------------ SETTERS ------------

        ///Set relative frame transform
        void set_transform(const transform2& tform) noexcept;

        ///Set transform scale as absolute (ignore parent scale)
        void set_transform_scale_absolute(bool enabled) noexcept;

        ///Set relative frame transform
        void set_transform(transform2&& tform) noexcept;

        ///Set relative frame transform position
        void set_position(vector2 offset) noexcept;

        ///Set relative frame transform rotation
        void set_rotation(float rotation) noexcept;

        ///Set relative frame transform scale
        void set_scale(vector2 scale) noexcept;
    };
}