#include "transform2.hpp"

namespace rvi
{
    transform2 transform2::merge(const transform2& other) const noexcept
    {
        transform2 res = *this;
        res.position += other.position;
        res.rotation = math::clamp_angle_deg(res.rotation + other.rotation);
        res.scale *= other.scale;
        return res;
    }

    void transform2::merge_in_place(const transform2& other) noexcept
    {
        position += other.position;
        rotation = math::clamp_angle_deg(rotation + other.rotation);
        scale *= other.scale;
    }

    bool transform2::operator==(const transform2& other) const noexcept
    {
        return (position == other.position) 
            && (scale == other.scale) 
            && (rotation == other.rotation);
    }

    bool transform2::operator!=(const transform2& other) const noexcept
    {
        return (position != other.position) 
            || (scale != other.scale) 
            || (rotation != other.rotation);
    }
}