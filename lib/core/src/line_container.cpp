#include <rvi/line_container.hpp>

#include <rvi/assert.hpp>
#include <rvi/cpu_support.hpp>
#include <rvi/vtable.hpp>
#include <thread>

namespace rvi
{
    //---------------------------------------
    // VTable functions forward declarations
    //---------------------------------------
    #if CURRENT_ARCH_X86_64 || CURRENT_ARCH_X86_32

    void apply_transform_sse(line_container&, const transform2&);
    void apply_offset_sse(line_container&, const vector2&);
    void apply_scale_both_sse(line_container&, const vector2&);
    void apply_scale_start_sse(line_container&, const vector2&);
    void apply_scale_end_sse(line_container&, const vector2&);
    void apply_rotation_sse(line_container&, float);

    void apply_transform_avx(line_container&, const transform2&);
    void apply_offset_avx(line_container&, const vector2&);
    void apply_scale_both_avx(line_container&, const vector2&);
    void apply_scale_start_avx(line_container&, const vector2&);
    void apply_scale_end_avx(line_container&, const vector2&);
    void apply_rotation_avx(line_container&, float);
    
    #endif

    void apply_transform_std(line_container&, const transform2&);
    void apply_offset_std(line_container&, const vector2&);
    void apply_scale_both_std(line_container&, const vector2&);
    void apply_scale_start_std(line_container&, const vector2&);
    void apply_scale_end_std(line_container&, const vector2&);
    void apply_rotation_std(line_container&, float);

    //---------------------------------
    // Line container vtable structure
    //---------------------------------
    struct _lc_vtable : public vtable<line_container>
    {
        VT_ENTRY<const transform2&> apply_transform;
        VT_ENTRY<const vector2&> apply_offset;
        VT_ENTRY<const vector2&> apply_scale_both;
        VT_ENTRY<const vector2&> apply_scale_start;
        VT_ENTRY<const vector2&> apply_scale_end;
        VT_ENTRY<float> apply_rotation;
    };

    //------------------
    // Vtable generator 
    //------------------
    _lc_vtable gen_vtable()
    {
        _lc_vtable result;
        
        #if CURRENT_ARCH_X86_64 || CURRENT_ARCH_X86_32
        if(cpu_support::x86::get_feature(cpu_support::x86::feature::AVX))
        {
            result.apply_offset = &apply_offset_avx;
            result.apply_scale_both = &apply_scale_both_avx;
            result.apply_scale_end = &apply_scale_end_avx;
            result.apply_scale_start = &apply_scale_start_avx;
            result.apply_transform = &apply_transform_avx;
            result.apply_rotation = &apply_rotation_avx;
        }
        else if(cpu_support::x86::get_feature(cpu_support::x86::feature::SSE))
        {
            result.apply_offset = &apply_offset_sse;
            result.apply_scale_both = &apply_scale_both_sse;
            result.apply_scale_end = &apply_scale_end_sse;
            result.apply_scale_start = &apply_scale_start_sse;
            result.apply_transform = &apply_transform_sse;
            result.apply_rotation = &apply_rotation_sse;
        }
        else
        {
            result.apply_offset = &apply_offset_std;
            result.apply_scale_both = &apply_scale_both_std;
            result.apply_scale_end = &apply_scale_end_std;
            result.apply_scale_start = &apply_scale_start_std;
            result.apply_transform = &apply_transform_std;
            result.apply_rotation = &apply_rotation_std;
        }
        #else
        result.apply_offset = &apply_offset_std;
        result.apply_scale_both = &apply_scale_both_std;
        result.apply_scale_end = &apply_scale_end_std;
        result.apply_scale_start = &apply_scale_start_std;
        result.apply_transform = &apply_transform_std;
        result.apply_rotation = &apply_rotation_std;
        #endif

        result.initialized = true;
        return result;
    }

    //---------------
    // Global vtable
    //---------------
    _lc_vtable vtable = gen_vtable();

    void line_container::clear() noexcept
    {
        _positions.clear();
        _colors.clear();
    }

    void line_container::reserve(size_t sz)
    {
        _positions.reserve(sz * 4);
        _colors.reserve(sz * 2);
    }

    size_t line_container::size() const noexcept
    {
        return _positions.size() / 4;
    }

    bool line_container::empty() const noexcept
    {
        return _positions.size() == 0;
    }

    void line_container::push_back(vector2 s_pos, color_rgba s_col, vector2 e_pos, color_rgba e_col)
    {
        _positions.push_back(s_pos.x);
        _positions.push_back(s_pos.y);
        _positions.push_back(e_pos.x);
        _positions.push_back(e_pos.y);
        _colors.push_back(s_col.rgba());
        _colors.push_back(e_col.rgba());
    }
    
    void line_container::copy_into(line_container& target)
    {
        target._positions.reserve(target._positions.size() + _positions.size());
        target._colors.reserve(target._colors.size() + _colors.size());

        std::copy(_positions.begin(), _positions.end(), std::back_inserter(target._positions));
        std::copy(_colors.begin(), _colors.end(), std::back_inserter(target._colors));
    }

    void line_container::move_into(line_container& target)
    {
        target._positions.reserve(target._positions.size() + _positions.size());
        target._colors.reserve(target._colors.size() + _colors.size());

        std::move(_positions.begin(), _positions.end(), std::back_inserter(target._positions));
        std::move(_colors.begin(), _colors.end(), std::back_inserter(target._colors));
    }

    void line_container::transform_positions(std::function<void(line_span)> func, bool parallel)
    {
        rt_assert(_positions.size() % 4 == 0, "line_container position data is corrupted!");

        // Minimum elements per thread to allow parallel algorithm
        const unsigned int MIN_ELEMS_PER_THREAD_FOR_PARALLEL = 128;

        static const unsigned int max_threads = std::thread::hardware_concurrency();
        bool parallel_enabled = 
            parallel && 
            max_threads > 1 && 
            size() > (max_threads * MIN_ELEMS_PER_THREAD_FOR_PARALLEL);

        //+-+-+-+-+-+-+-+-+-+-+
        // Parallel
        //+-+-+-+-+-+-+-+-+-+-+
        if (parallel_enabled) 
        {
            std::vector<std::thread> threads;
            threads.reserve(max_threads);

            auto thread_act = [&](size_t idx_start, size_t idx_end)
            {
                for(auto i = idx_start; i < idx_end; i += 4)
                {
                    func(line_span(&_positions[i]));
                }
            };

            // -- First n-1 threads --
            size_t th_range_sz = size() / max_threads;
            for(size_t th_idx = 0; th_idx < max_threads - 1; th_idx++)
            {
                size_t idx_start = th_range_sz * th_idx;
                size_t idx_end = idx_start + th_range_sz;

                threads.push_back(std::thread(thread_act, idx_start, idx_end));
            }
            // -- Last thread [n] --
            size_t idx_start = th_range_sz * (max_threads - 1);
            size_t idx_end = _positions.size();
            std::thread(thread_act, idx_start, idx_end).join();

            // Wait for all other threads to finish
            for(auto& th : threads) { th.join(); }
        }
        //+-+-+-+-+-+-+-+-+-+-+
        // Single-threaded
        //+-+-+-+-+-+-+-+-+-+-+
        else
        {
            for(size_t i = 0; i < _positions.size(); i += 4)
            {
                func(line_span(&_positions[i]));
            }
        }
    }

    void line_container::apply_offset(vector2 offset)
    {
        if(offset == transform2::default_value().position) { return; }
        debug_assert(vtable.initialized, "Vtable not initialized!");
        vtable.apply_offset(*this, offset);
    }

    void line_container::apply_scale_end(vector2 scale)
    {
        if(scale == transform2::default_value().scale) { return; }
        debug_assert(vtable.initialized, "Vtable not initialized!");
        vtable.apply_scale_end(*this, scale);
    }

    void line_container::apply_scale_both(vector2 scale)
    {
        if(scale == transform2::default_value().scale) { return; }
        debug_assert(vtable.initialized, "Vtable not initialized!");
        vtable.apply_scale_both(*this, scale);
    }

    void line_container::apply_rotation(float angle)
    {
        if(angle == 0.0F) { return; }
        debug_assert(vtable.initialized, "Vtable not initialized!");
        vtable.apply_rotation(*this, angle);
    }

    void line_container::apply_transform(const transform2& tform)
    {
        if(tform == transform2::default_value()) { return; }
        debug_assert(vtable.initialized, "Vtable not initialized!");
        vtable.apply_transform(*this, tform);
    }

    float* line_container::position_buff()
    {
        return _positions.data();
    }
    
    uint32_t* line_container::color_buff()
    {
        return _colors.data();
    }

    std::vector<float>::const_iterator line_container::position_cbegin()
    {
        return _positions.cbegin();
    }

    std::vector<float>::const_iterator line_container::position_cend()
    {
        return _positions.cend();
    }

    std::vector<uint32_t>::const_iterator line_container::color_cbegin()
    {
        return _colors.cbegin();
    }

    std::vector<uint32_t>::const_iterator line_container::color_cend()
    {
        return _colors.cend();
    }

    std::vector<float>::iterator line_container::position_begin()
    {
        return _positions.begin();
    }

    std::vector<float>::iterator line_container::position_end()
    {
        return _positions.end();
    }

    std::vector<uint32_t>::iterator line_container::color_begin()
    {
        return _colors.begin();
    }
    
    std::vector<uint32_t>::iterator line_container::color_end()
    {
        return _colors.end();
    }

    float* line_container::positions_data()
    {
        return _positions.data();
    }

    uint32_t* line_container::colors_data()
    {
        return _colors.data();
    }

    //----------------------------------------
    // Vtable methods standard implementation
    //----------------------------------------
    void apply_transform_std(line_container& lc, const transform2& tform)
    {
        bool scale = tform.scale != transform2::default_value().scale;
        bool position = tform.position != transform2::default_value().position;
        bool rotation = tform.rotation != transform2::default_value().rotation;

        const float radAngle = rvi::math::deg2rad(tform.rotation);
        const float angleSin = std::sin(radAngle);
        const float angleCos = std::cos(radAngle);

        float* pos_ptr = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            // -- SCALE --
            if(scale)
            {
                pos_ptr[i + 0] *= tform.scale.x; //end
                pos_ptr[i + 1] *= tform.scale.y;
                pos_ptr[i + 2] *= tform.scale.x; //end
                pos_ptr[i + 3] *= tform.scale.y;
            }

            // -- ROTATION --
            if(rotation)
            {
                pos_ptr[i + 2] -= pos_ptr[i + 0];
                pos_ptr[i + 3] -= pos_ptr[i + 1];
            
                const float aux_x = pos_ptr[i + 2];
                const float aux_y = pos_ptr[i + 3];

                // [rx] = [cos(a) , -sin(a)][x]
                pos_ptr[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
                // [ry] = [sin(a) ,  cos(a)][y]
                pos_ptr[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);

                pos_ptr[i + 2] += pos_ptr[i + 0];
                pos_ptr[i + 3] += pos_ptr[i + 1];
            }

            if(position)
            {
                // -- OFFSET --
                pos_ptr[i + 0] += tform.position.x; //start
                pos_ptr[i + 1] += tform.position.y;
                pos_ptr[i + 2] += tform.position.x; //end
                pos_ptr[i + 3] += tform.position.y;
            }
        }
    }

    void apply_offset_std(line_container& lc , const vector2& offset)
    {
        float* pos_ptr = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            pos_ptr[i + 0] += offset.x; //start
            pos_ptr[i + 1] += offset.y;
            pos_ptr[i + 2] += offset.x; //end
            pos_ptr[i + 3] += offset.y;
        }
    }

    void apply_rotation_std(line_container& lc, float rotation)
    {
        const float radAngle = math::deg2rad(rotation);
        const float angleSin = std::sin(radAngle);
        const float angleCos = std::cos(radAngle);

        float* pos_ptr = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            pos_ptr[i + 2] -= pos_ptr[i + 0];
            pos_ptr[i + 3] -= pos_ptr[i + 1];
        
            const float aux_x = pos_ptr[i + 2];
            const float aux_y = pos_ptr[i + 3];

            // [rx] = [cos(a) , -sin(a)][x]
            pos_ptr[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
            // [ry] = [sin(a) ,  cos(a)][y]
            pos_ptr[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);

            pos_ptr[i + 2] += pos_ptr[i + 0];
            pos_ptr[i + 3] += pos_ptr[i + 1];
        }
    }

    void apply_scale_both_std(line_container& lc, const vector2& scale)
    {
        float* pos_ptr = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            pos_ptr[i + 0] *= scale.x;
            pos_ptr[i + 1] *= scale.y;
            pos_ptr[i + 2] *= scale.x;
            pos_ptr[i + 3] *= scale.y;
        }
    }

    void apply_scale_start_std(line_container& lc, const vector2& scale)
    {
        float* pos_ptr = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            pos_ptr[i + 0] *= scale.x;
            pos_ptr[i + 1] *= scale.y;
        }
    }

    void apply_scale_end_std(line_container& lc, const vector2& scale)
    {
        float* pos_ptr = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            pos_ptr[i + 2] *= scale.x;
            pos_ptr[i + 3] *= scale.y;
        }
    }

    //----------------------------------------------
    // Vtable methods SSE-vectorized implementation
    //----------------------------------------------
    #if CURRENT_ARCH_X86_64 || CURRENT_ARCH_X86_32
    #include <xmmintrin.h>
    #include <rvi/math.hpp>

    void apply_transform_sse(line_container& lc, const transform2& tform)
    {
        float _iv_zero[4] = { 0, 0, 0, 0 };
        __m128 vzero = _mm_load_ps(_iv_zero);

        float _iv_scale[4] = { tform.scale.x, tform.scale.y, tform.scale.x, tform.scale.y };
        __m128 vscale = _mm_load_ps(_iv_scale);

        float _iv_position[4] = { tform.position.x, tform.position.y, tform.position.x, tform.position.y };
        __m128 vposition = _mm_load_ps(_iv_position); 

        const float rad_angle = math::deg2rad(tform.rotation);
        const float angle_sin = std::sin(rad_angle);
        const float angle_cos = std::cos(rad_angle);
        float _iv_rot_table[4] = { angle_cos, -angle_sin, angle_sin, angle_cos };
        __m128 vrot_table = _mm_load_ps(_iv_rot_table);

        float* _fptr0 = lc.positions_data();

        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            float* fptr = _fptr0 + i;
            __m128 vvec = _mm_load_ps(fptr);

            // -- SCALE --
            vvec = _mm_mul_ps(vvec, vscale);
            __m128 vspos = _mm_movelh_ps(vvec, vzero); // f[0], f[1], 0, 0

            // -- ROTATION --
            float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
            __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
            vtemp_rot_subadd = _mm_mul_ps(vtemp_rot_subadd, vscale);
            vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
            __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
            vhi = _mm_mul_ps(vhi, vrot_table);
            vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
            vhi = _mm_movehl_ps(vhi, vzero); // 0, 0, x, y
            vvec = _mm_or_ps(vspos, vhi);
            vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
        
            // -- OFFSET --
            vvec = _mm_add_ps(vvec, vposition);
            
            _mm_store_ps(fptr, vvec);
        }
    }

    void apply_offset_sse(line_container& lc, const vector2& offset)
    {
        float _iv_offset[4] = { offset.x, offset.y, offset.x, offset.y };
        __m128 voffset = _mm_load_ps(_iv_offset);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            float* fptr = fptr0 + i;
            __m128 vpos = _mm_load_ps(fptr);
            _mm_store_ps(fptr, _mm_add_ps(vpos, voffset));
        }
    }

    void apply_scale_both_sse(line_container& lc, const vector2& scale)
    {
        float _iv_scale[4] = { scale.x, scale.y, scale.x, scale.y };
        __m128 vscale = _mm_load_ps(_iv_scale);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            float* fptr = fptr0 + i;
            __m128 vpos = _mm_load_ps(fptr);
            _mm_store_ps(fptr, _mm_mul_ps(vpos, vscale));
        }
    }

    void apply_scale_start_sse(line_container& lc, const vector2& scale)
    {
        float _iv_scale[4] = { scale.x, scale.y, 1.0F, 1.0F };
        __m128 vscale = _mm_load_ps(_iv_scale);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            float* fptr = fptr0 + i;
            __m128 vpos = _mm_load_ps(fptr);
            _mm_store_ps(fptr, _mm_mul_ps(vpos, vscale));
        }
    }

    void apply_scale_end_sse(line_container& lc, const vector2& scale)
    {
        float _iv_scale[4] = { 1.0F, 1.0F, scale.x, scale.y };
        __m128 vscale = _mm_load_ps(_iv_scale);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            float* fptr = fptr0 + i;
            __m128 vpos = _mm_load_ps(fptr);
            _mm_store_ps(fptr, _mm_mul_ps(vpos, vscale));
        }
    }

    void apply_rotation_sse(line_container& lc, float angle)
    {
        const float rad_angle = math::deg2rad(angle);
        const float angle_sin = std::sin(rad_angle);
        const float angle_cos = std::cos(rad_angle);
        float _iv_rot_table[4] = { angle_cos, -angle_sin, angle_sin, angle_cos };
        __m128 vrot_table = _mm_load_ps(_iv_rot_table);

        float _iv_zero[4] = { 0, 0, 0, 0 };
        __m128 vzero = _mm_load_ps(_iv_zero);

        float* _fptr0 = lc.positions_data();

        for(size_t i = 0; i < lc.size() * 4; i += 4)
        {
            float* fptr = _fptr0 + i;
            __m128 vvec = _mm_load_ps(fptr);

            __m128 vspos = _mm_movelh_ps(vvec, vzero); // f[0], f[1], 0, 0

            float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
            __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
            vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
            __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
            vhi = _mm_mul_ps(vhi, vrot_table);
            vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
            vhi = _mm_movehl_ps(vhi, vzero); // 0, 0, x, y
            vvec = _mm_or_ps(vspos, vhi);
            vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
            _mm_store_ps(fptr, vvec);
        }
    }


    //----------------------------------------------
    // Vtable methods AVX-vectorized implementation
    //----------------------------------------------
    #include <immintrin.h>

    void apply_transform_avx(line_container& lc, const transform2& tform) 
    {
        rt_assert(false, "Not implemented!");
    }

    void apply_offset_avx(line_container& lc, const vector2& offset)
    {
        const float& x = offset.x;
        const float& y = offset.y;
        float _iv_offset[8] = { x, y, x, y, x, y, x, y };
        __m256 voffset = _mm256_load_ps(_iv_offset);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 8)
        {
            float* fptr = fptr0 + i;
            __m256 vpos = _mm256_load_ps(fptr);
            vpos = _mm256_add_ps(vpos, voffset);
            _mm256_store_ps(fptr, vpos);
        }

        // Remaining line, for odd line sizes
        if((lc.size() % 2) == 1)
        {
            float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
            fptr[0] += x;
            fptr[1] += y;
            fptr[2] += x;
            fptr[3] += y;
        }
    }

    void apply_scale_both_avx(line_container& lc, const vector2& scale)
    {
        const float& x = scale.x;
        const float& y = scale.y;
        float _iv_scale[8] = { x, y, x, y, x, y, x, y };
        __m256 vscale = _mm256_load_ps(_iv_scale);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 8)
        {
            float* fptr = fptr0 + i;
            __m256 vpos = _mm256_load_ps(fptr);
            vpos = _mm256_mul_ps(vpos, vscale);
            _mm256_store_ps(fptr, vpos);
        }

        // Remaining line, for odd line sizes
        if((lc.size() % 2) == 1)
        {
            float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
            fptr[0] *= x;
            fptr[1] *= y;
            fptr[2] *= x;
            fptr[3] *= y;
        }
    }

    void apply_scale_start_avx(line_container& lc, const vector2& scale)
    {
        const float& x = scale.x;
        const float& y = scale.y;
        float _iv_scale[8] = { x, y, 1, 1, x, y, 1, 1 };
        __m256 vscale = _mm256_load_ps(_iv_scale);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 8)
        {
            float* fptr = fptr0 + i;
            __m256 vpos = _mm256_load_ps(fptr);
            vpos = _mm256_mul_ps(vpos, vscale);
            _mm256_store_ps(fptr, vpos);
        }

        // Remaining line, for odd line sizes
        if((lc.size() % 2) == 1)
        {
            float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
            fptr[0] *= x;
            fptr[1] *= y;
        }
    }

    void apply_scale_end_avx(line_container& lc, const vector2& scale)
    {
        const float& x = scale.x;
        const float& y = scale.y;
        float _iv_scale[8] = { 1, 1, x, y, 1, 1, x, y };
        __m256 vscale = _mm256_load_ps(_iv_scale);

        float* fptr0 = lc.positions_data();
        for(size_t i = 0; i < lc.size() * 4; i += 8)
        {
            float* fptr = fptr0 + i;
            __m256 vpos = _mm256_load_ps(fptr);
            vpos = _mm256_mul_ps(vpos, vscale);
            _mm256_store_ps(fptr, vpos);
        }

        // Remaining line, for odd line sizes
        if((lc.size() % 2) == 1)
        {
            float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
            fptr[2] *= x;
            fptr[3] *= y;
        }
    }

    void apply_rotation_avx(line_container& lc, float angle)
    {
        const float rad_angle = math::deg2rad(angle);
        const float angle_sin = std::sin(rad_angle);
        const float angle_cos = std::cos(rad_angle);
        
        float _iv_rot_table[8] = { 
            angle_cos, -angle_sin, angle_sin, angle_cos,
            angle_cos, -angle_sin, angle_sin, angle_cos
        };
        __m256 vrot_table = _mm256_load_ps(_iv_rot_table);

        float _iv_zero[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        __m256 vzero = _mm256_load_ps(_iv_zero);

        float* _fptr0 = lc.positions_data();

        for(size_t i = 0; i < lc.size() * 4; i += 8)
        {
            float* fptr = _fptr0 + i;
            __m256 vvec = _mm256_load_ps(fptr);

            __m256 vspos = _mm256_blend_ps(vzero, vvec, 0b11001100);

            float _iv_rotator_temp_subadd[8] { 
                0, 0, fptr[0], fptr[1],
                0, 0, fptr[4], fptr[5]
            };
            __m256 vtemp_rot_subadd = _mm256_load_ps(_iv_rotator_temp_subadd);
            vvec = _mm256_sub_ps(vvec, vtemp_rot_subadd);
            __m256 vhi = _mm256_unpackhi_ps(vvec, vvec);
            vhi = _mm256_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
            vhi = _mm256_mul_ps(vhi, vrot_table);
            vhi = _mm256_add_ps(vhi, _mm256_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
            vhi = _mm256_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
            vhi = _mm256_blend_ps(vzero, vhi, 0b00110011); // 0, 0, x, y
            vvec = _mm256_or_ps(vspos, vhi);
            vvec = _mm256_add_ps(vvec, vtemp_rot_subadd);
            _mm256_store_ps(fptr, vvec);
        }

        // Remainder (4 floats -> SSE)
        if(lc.size() % 2 == 1)
        {
            float* fptr = _fptr0 + ((lc.size() - 1) * 4);
            __m128 vzero_sse = _mm_load_ps(_iv_zero);
            __m128 vrot_table_sse = _mm_load_ps(_iv_rot_table);

            __m128 vvec = _mm_load_ps(fptr);
            __m128 vspos = _mm_movelh_ps(vvec, vzero_sse); // f[0], f[1], 0, 0

            float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
            __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
            vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
            __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
            vhi = _mm_mul_ps(vhi, vrot_table_sse);
            vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
            vhi = _mm_movehl_ps(vhi, vzero_sse); // 0, 0, x, y
            vvec = _mm_or_ps(vspos, vhi);
            vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
            _mm_store_ps(fptr, vvec);
        }
    }

#endif
}