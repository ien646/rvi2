#include "vertex.hpp"

namespace rvi
{
    vertex::vertex(vector2 pos, color_rgba vx_color) noexcept
        : position(pos)
        , color(vx_color)
    { }

    vertex::vertex(float x, float y) noexcept
        : position(vector2(x, y))
    { }

    vertex::vertex(float x, float y, u8 r, u8 g, u8 b, u8 a) noexcept
        : position(vector2(x, y))
        , color(color_rgba(r, g, b, a))
    { }

    vertex::vertex(vector2 pos) noexcept
        : position(pos)
    { }

    std::string vertex::to_string() const
    {
        std::stringstream ss;
        ss << "[{POS}:"
            << position.to_string()
            << ",{COLOR}:"
            << color.to_string()
            << "]";
        return ss.str();
    }

    bool vertex::operator==(vertex other) const noexcept
    {
        return (position == other.position) && (color == other.color);
    }

    bool vertex::operator!=(vertex other) const noexcept
    {
        return (position != other.position) || (color != other.color);
    }
}