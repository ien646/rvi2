#include "transform2.hpp"

namespace rvi
{
    Transform2 Transform2::Merge(const Transform2& other) const noexcept
    {
        Transform2 res = *this;
        res.Position += other.Position;
        res.Rotation += Math::ClampAngleDeg(other.Rotation);
        res.Scale *= other.Scale;
        return res;
    }
}