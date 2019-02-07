#pragma once

#include <vector>
#include <utility>

#include <rvi/base.hpp>
#include <rvi/vector2.hpp>
#include <rvi/color_rgba.hpp>
#include <rvi/transform2.hpp>

namespace rvi
{
    class line_container
    {
    private:
        std::vector<float> _positions;
        std::vector<uint32_t> _colors;

    public:

        void clear() noexcept;

        void reserve(size_t sz);

        size_t size() const noexcept;
        void push_back(vector2 s_pos, color_rgba s_col, vector2 e_pos, color_rgba e_col);

        void copy_into(line_container& target);
        void move_into(line_container& target);

        void transform_pos_in_place(std::function<void(float*)> func);

        void apply_offset(vector2 offset);
        void apply_scale_end(vector2 scale);
        void apply_scale_both(vector2 scale);
        void apply_rotation(float angle);
        void apply_transform(const transform2& tform);

        float* position_buff();
        uint32_t* color_buff();

        std::vector<float>::const_iterator position_cbegin();
        std::vector<float>::const_iterator position_cend();

        std::vector<uint32_t>::const_iterator color_cbegin();
        std::vector<uint32_t>::const_iterator color_cend();
    };
};