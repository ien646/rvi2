#include <rvi/rectangle.hpp>

namespace rvi
{
    rectangle::rectangle(float x, float y, float w, float h)
        : position(x, y)
        , size(w, h)
    { }

    rectangle::rectangle(vector2 pos, vector2 sz)
        : position(pos)
        , size(sz)
    { }

    float rectangle::left() const noexcept
    {
        return position.x;
    }

    float rectangle::right() const noexcept
    {
        return position.x + size.x;
    }

    float rectangle::bottom() const noexcept
    {
        return position.y;
    }

    float rectangle::top() const noexcept
    {
        return position.y + size.y;
    }

    vector2 rectangle::corner_left_top() const noexcept
    {
        return vector2(left(), top());
    }

    vector2 rectangle::corner_right_top() const noexcept
    {
        return vector2(right(), top());
    }
            
    vector2 rectangle::corner_left_bottom() const noexcept
    {
        return position;
    }

    vector2 rectangle::corner_right_bottom() const noexcept
    {
        return vector2(right(), bottom());
    }

    bool rectangle::operator==(const rectangle& other) const noexcept
    {
        return (position == other.position) && (size == other.size);
    }

    bool rectangle::operator!=(const rectangle& other) const noexcept
    {
        return (position != other.position) || (size != other.size);
    }

    bool rectangle::contains(vector2 point) const noexcept
    {
        return (point.x >= left())
            && (point.x <= right())
            && (point.y >= bottom())
            && (point.y <= top());
    }

    bool rectangle::contains(const rectangle& other) const noexcept
    {
        return (this->contains(other.position))
            && (this->contains(other.corner_right_top()));
    }

    bool rectangle::intersects(const rectangle& other) const noexcept
    {
        return left() <= other.right() 
            && right() >= other.left() 
            && top() >= other.bottom() 
            && bottom() <= other.top();
    }
}