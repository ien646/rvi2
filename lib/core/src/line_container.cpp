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
        if(offset != transform2::default_value().position)
        {
            for(size_t i = 0; i < _positions.size(); i += 4)
            {
                _positions[i + 0] += offset.x; //start
                _positions[i + 1] += offset.y;
                _positions[i + 2] += offset.x; //end
                _positions[i + 3] += offset.y;
            }
        }
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

                const float radAngle = rvi::math::deg2rad(angle);
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
}
