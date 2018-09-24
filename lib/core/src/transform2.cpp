#include "transform2.hpp"

namespace rvi
{
    Transform2 Transform2::Merge(const Transform2& other) const noexcept
    {
        Transform2 res = *this;
        res.Position += other.Position;
        res.Rotation = Math::ClampAngleDeg(res.Rotation+ other.Rotation);
        res.Scale *= other.Scale;
        return res;
    }

    bool Transform2::operator==(const Transform2& other) const noexcept
    {
        return (Position == other.Position) 
            && (Scale == other.Scale) 
            && (Rotation == other.Rotation);
    }

    bool Transform2::operator!=(const Transform2& other) const noexcept
    {
        return (Position != other.Position) 
            || (Scale != other.Scale) 
            || (Rotation != other.Rotation);
    }
}