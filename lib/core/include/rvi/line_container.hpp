#pragma once

#include <vector>
#include <utility>

#include <rvi/base.hpp>
#include <rvi/vector2.hpp>
#include <rvi/color_rgba.hpp>
#include <rvi/transform2.hpp>

namespace rvi
{
    class line_position_data
    {
    private:
        float* _ptr;
    public:
        line_position_data(float* ptr)
            : _ptr(ptr) { }

        vector2 start()     { return vector2(_ptr[0], _ptr[1]); }
        vector2 end()       { return vector2(_ptr[2], _ptr[3]); }
        float* start_ptr()  { return &_ptr[0]; }
        float* end_ptr()    { return &_ptr[2]; }
    };

    class line_color_data
    {
    private:
        color_rgba* _ptr;

    public:
        line_color_data(color_rgba* ptr)
            : _ptr(ptr) { }

        color_rgba start()      { return _ptr[0]; }
        color_rgba end()        { return _ptr[1]; }
        color_rgba* start_ptr() { return &_ptr[0]; }
        color_rgba* end_ptr()   { return &_ptr[1]; }
    };

    class line_container
    {
    private:
        std::vector<float> _positions;
        std::vector<color_rgba> _colors;

    public:
        line_position_data position_data_at(size_t index);
        line_color_data color_data_at(size_t index);

        size_t size() const noexcept;
        void push_back(vector2 s_pos, color_rgba s_col, vector2 e_pos, color_rgba e_col);

        void transform_pos_in_place(std::function<void(float*)> func);

        void apply_offset(vector2 offset);
        void apply_scale_end(vector2 scale);
        void apply_scale_both(vector2 scale);
        void apply_rotation(float angle);
        void apply_transform(const transform2& tform);
    };
};