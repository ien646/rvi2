#pragma once

#include <vector>
#include <utility>

#include <rvi/base.hpp>
#include <rvi/vector2.hpp>
#include <rvi/color_rgba.hpp>
#include <rvi/transform2.hpp>
#include <rvi/cpu_support.hpp>

namespace rvi
{
    /**
     * @brief Line-object view for line_container class
     */
    class line_span
    {
    private:
        float* _ptr;

    public:
        ///Start vertex coordinate x-value
        float& start_x;
        ///Start vertex coordinate y-value
        float& start_y;
        ///End vertex coordinate x-value
        float& end_x;
        ///End vertex coordinate y-value
        float& end_y;

        line_span(float* lptr)
            : _ptr(lptr)
            , start_x(_ptr[0])
            , start_y(_ptr[1])
            , end_x(_ptr[2])
            , end_y(_ptr[3])
        { }

        ///Obtain a raw pointer to the underlying array
        float* data() { return _ptr; }
        float& operator[](size_t index) { return _ptr[index]; }
    };

    /**
     * @brief SOA-Style line data container 
     */
    class line_container
    {
    private:
        std::vector<float> _positions;
        std::vector<uint32_t> _colors;

    public:
        ///Clear all lines contained
        void clear() noexcept;

        ///Reserve space to hold at least 'sz' items
        void reserve(size_t sz);

        ///Contained line count
        size_t size() const noexcept;

        ///Check if the container has no lines
        bool empty() const noexcept;

        /**
         * @brief Insert a new line at the back of the container
         * 
         * @param Start vertex position 
         * @param Start vertex color
         * @param End vertex position
         * @param End vertex color
         */
        void push_back(vector2 s_pos, color_rgba s_col, vector2 e_pos, color_rgba e_col);

        ///Copy contained lines into another container
        void copy_into(line_container& target);
        
        ///Move contained lines into another container
        void move_into(line_container& target);

        /**
         * @brief Apply a transforming operation to all the lines in the container. 
         * 
         * @param func Function to apply
         * @param parallel If true, execution might be paralellized to improve performance.
         */
        void transform_positions(std::function<void(line_span)> func, bool parallel = false);

        ///Apply a 2D offset to all the lines in the container
        void apply_offset(vector2 offset);

        /**
         * @brief Apply a 2D scale to all the end vertices 
         * from the lines in the container
         * 
         * @param scale Scale to apply
         */
        void apply_scale_end(vector2 scale);

        /**
         * @brief Apply a 2D scale to all the start and end vertices 
         * from the lines in the container
         * 
         * @param scale Scale to apply
         */
        void apply_scale_both(vector2 scale);

        ///Apply a rotation angle (in degrees) to all the lines in the container
        void apply_rotation(float angle);

        /**
         * @brief Apply a transform's properties (offset, scale, rotation) 
         * to all the lines in the container
         * @param tform 
         */
        void apply_transform(const transform2& tform);

        ///Obtain a raw pointer to the lines position-buffer of the container
        float* position_buff();

        ///Obtain a raw pointer to the lines color-buffer of the container
        uint32_t* color_buff();

        ///Constant begin iterator of the lines position-buffer
        std::vector<float>::const_iterator position_cbegin();

        ///Constant end iterator of the lines position-buffer
        std::vector<float>::const_iterator position_cend();

        ///Constant begin iterator of the lines color-buffer
        std::vector<uint32_t>::const_iterator color_cbegin();

        ///Constant end iterator of the lines color-buffer
        std::vector<uint32_t>::const_iterator color_cend();

        ///Begin iterator of the lines position-buffer
        std::vector<float>::iterator position_begin();

        ///End iterator of the lines position-buffer
        std::vector<float>::iterator position_end();

        ///Begin iterator of the lines color-buffer
        std::vector<uint32_t>::iterator color_begin();

        ///End iterator of the lines color-buffer
        std::vector<uint32_t>::iterator color_end();

    private:
    #if CURRENT_ARCH_X86_32 || CURRENT_ARCH_X86_64
        void apply_transform_sse(const transform2& tform);
        void apply_offset_sse(const vector2& offset);
    #endif
    };
}