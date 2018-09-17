#include "line.hpp"

namespace rvi
{
    Line::Line(const Vertex& start, const Vertex& end) noexcept
        : Start(start)
        , End(end)
    { }

    Line::Line(Vertex&& start, Vertex&& end) noexcept
        : Start(std::move(start))
        , End(std::move(end))
    { }

    void Line::ApplyTransform(const Transform2& tform) noexcept
    {
        Start.ApplyTransform(tform);
        End.ApplyTransform(tform);
    }

    bool Line::operator==(Line other) const noexcept
    {
        return (Start == other.Start) && (End == other.End);
    }

    bool Line::operator!=(Line other) const noexcept
    {
        return (Start != other.Start) || (End != other.End);
    }
}