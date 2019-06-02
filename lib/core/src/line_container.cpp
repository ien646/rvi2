#include <rvi/line_container.hpp>

#include <rvi/assert.hpp>
#include <thread>

namespace rvi
{
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
        r_assert(_positions.size() % 4 == 0, "line_container position data is corrupted!");

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

        #if CURRENT_ARCH_X86_64
        apply_offset_sse(offset);

        #elif CURRENT_ARCH_X86_32
        if(cpu_support::x86::get_feature(cpu_support::x86::feature::SSE))
        {
            apply_offset_sse(offset);
        }

        #else
        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            _positions[i + 0] += offset.x; //start
            _positions[i + 1] += offset.y;
            _positions[i + 2] += offset.x; //end
            _positions[i + 3] += offset.y;
        }
        #endif
    }

    void line_container::apply_scale_end(vector2 scale)
    {
        if(scale != transform2::default_value().scale)
        {
            for(size_t i = 0; i < _positions.size(); i += 4)
            {
                _positions[i + 2] *= scale.x; //end
                _positions[i + 3] *= scale.y;
            }
        }
    }

    void line_container::apply_scale_both(vector2 scale)
    {
        if(scale != transform2::default_value().scale)
        {
            for(size_t i = 0; i < _positions.size(); i += 4)
            {
                _positions[i + 0] *= scale.x; //end
                _positions[i + 1] *= scale.y;
                _positions[i + 2] *= scale.x; //end
                _positions[i + 3] *= scale.y;
            }
        }
    }

    void line_container::apply_rotation(float angle)
    {
        if(angle != 0.0F)
        {
            for(size_t i = 0; i < _positions.size(); i += 4)
            {
                _positions[i + 2] -= _positions[i + 0];
                _positions[i + 3] -= _positions[i + 1];

                const float radAngle = math::deg2rad(angle);
                const float angleSin = std::sin(radAngle);
                const float angleCos = std::cos(radAngle);
            
                const float aux_x = _positions[i + 2];
                const float aux_y = _positions[i + 3];

                // [rx] = [cos(a) , -sin(a)][x]
                _positions[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
                // [ry] = [sin(a) ,  cos(a)][y]
                _positions[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);

                _positions[i + 2] += _positions[i + 0];
                _positions[i + 3] += _positions[i + 1];
            }
        }
    }

    void line_container::apply_transform(const transform2& tform)
    {
        if(tform == transform2::default_value()) { return; }

        // All x86-64 cpus support at least SSE2
        #if CURRENT_ARCH_X86_64
        apply_transform_sse(tform);

        #elif CURRENT_ARCH_X86_32
        if(cpu_support::x86::get_feature(cpu_support::x86::feature::SSE))
        {
            apply_transform_sse(tform);
        }

        #else // Default
        bool scale = tform.scale != transform2::default_value().scale;
        bool position = tform.position != transform2::default_value().position;
        bool rotation = tform.rotation != transform2::default_value().rotation;

        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            // -- SCALE --
            if(scale)
            {
                _positions[i + 0] *= tform.scale.x; //end
                _positions[i + 1] *= tform.scale.y;
                _positions[i + 2] *= tform.scale.x; //end
                _positions[i + 3] *= tform.scale.y;
            }

            // -- ROTATION --
            if(rotation)
            {            
                _positions[i + 2] -= _positions[i + 0];
                _positions[i + 3] -= _positions[i + 1];            
            
                const float radAngle = rvi::math::deg2rad(tform.rotation);
                const float angleSin = std::sin(radAngle);
                const float angleCos = std::cos(radAngle);
            
                const float aux_x = _positions[i + 2];
                const float aux_y = _positions[i + 3];

                // [rx] = [cos(a) , -sin(a)][x]
                _positions[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
                // [ry] = [sin(a) ,  cos(a)][y]
                _positions[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);

                _positions[i + 2] += _positions[i + 0];
                _positions[i + 3] += _positions[i + 1];
            }

            if(position)
            {
                // -- OFFSET --
                _positions[i + 0] += tform.position.x; //start
                _positions[i + 1] += tform.position.y;
                _positions[i + 2] += tform.position.x; //end
                _positions[i + 3] += tform.position.y;
            }
        }
    #endif
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

#if CURRENT_ARCH_X86_64 || CURRENT_ARCH_X86_32
#include <xmmintrin.h>
#include <rvi/math.hpp>

    void line_container::apply_transform_sse(const transform2& tform)
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

        float* _fptr0 = _positions.data();

        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            float* fptr = _fptr0 + i;
            __m128 vvec = _mm_load_ps(fptr);      

            // -- SCALE --
            vvec = _mm_mul_ps(vvec, vscale);
            __m128 vspos = _mm_movehl_ps(vzero, vvec); // f[0], f[1], 0, 0

            // -- ROTATION --
            float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
            __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
            vtemp_rot_subadd = _mm_mul_ps(vtemp_rot_subadd, vscale);
            vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
            __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
            vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y            
            vhi = _mm_mul_ps(vhi, vrot_table);
            vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
            vhi = _mm_movehl_ps(vhi, vzero);
            vvec = _mm_or_ps(vspos, vhi);
            vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
        
            // -- OFFSET --
            vvec = _mm_add_ps(vvec, vposition);
            
            _mm_store_ps(fptr, vvec);
        }    
    }

    void line_container::apply_offset_sse(const vector2& offset)
    {
        if(offset == transform2::default_value().position) { return; }

        float _iv_offset[4] = { offset.x, offset.y, offset.x, offset.y };
        __m128 voffset = _mm_load_ps(_iv_offset);

        float* fptr0 = _positions.data();
        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            float* fptr = fptr0 + i;
            __m128 vpos = _mm_load_ps(fptr);
            _mm_store_ps(fptr, _mm_add_ps(vpos, voffset));
        }        
    }

#endif
}
