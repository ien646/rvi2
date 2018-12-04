#include "vertex.hpp"

namespace rvi
{
    vertex::vertex(vector2 pos, color_rgba vx_color) noexcept
        : position(pos)
        , color(vx_color)
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