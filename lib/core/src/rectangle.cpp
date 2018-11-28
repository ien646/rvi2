#include "rectangle.hpp"

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

    bool rectangle::operator==(const rectangle& other)
    {
        return (position == other.position) && (size == other.size);
    }

    bool rectangle::operator!=(const rectangle& other)
    {
        return (position != other.position) || (size != other.size);
    }
}