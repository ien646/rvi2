#include <rvi/line_container.hpp>

namespace rvi
{        
    line_position_data line_container::position_data_at(size_t index)
    {
        return line_position_data(&_positions[index * 4]);
    }
    
    line_color_data line_container::color_data_at(size_t index)
    {
        return line_color_data(&_colors[index * 2]);
    }

    size_t line_container::size() const noexcept
    {
        return _positions.size() / 4;
    }

    void line_container::push_back(vector2 s_pos, color_rgba s_col, vector2 e_pos, color_rgba e_col)
    {
        _positions.push_back(s_pos.x);
        _positions.push_back(s_pos.y);
        _positions.push_back(e_pos.x);
        _positions.push_back(e_pos.y);
        _colors.push_back(s_col);
        _colors.push_back(e_col);
    }

    void line_container::transform_pos_in_place(std::function<void(float*)> func)
    {
        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            func(&_positions[i]);
        }
    }

    void line_container::apply_offset(vector2 offset)
    {
        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            _positions[i + 0] += offset.x; //start
            _positions[i + 1] += offset.y;
            _positions[i + 2] += offset.x; //end
            _positions[i + 3] += offset.y;
        }
    }

    void line_container::apply_scale_end(vector2 scale)
    {
        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            _positions[i + 2] *= scale.x; //end
            _positions[i + 3] *= scale.y;
        }
    }

    void line_container::apply_scale_both(vector2 scale)
    {
        for(size_t i = 0; i < _positions.size(); i += 4)
        {
            _positions[i + 0] *= scale.x; //end
            _positions[i + 1] *= scale.y;
            _positions[i + 2] *= scale.x; //end
            _positions[i + 3] *= scale.y;
        }
    }

    void line_container::apply_rotation(float angle)
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

    void line_container::apply_transform(const transform2& tform)
    {
        apply_scale_both(tform.scale);
        apply_rotation(tform.rotation);
        apply_offset(tform.position);
    }
}
