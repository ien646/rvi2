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
    
    void Line::ApplyOffset(Vector2 offset)
    {
        Start.Position.OffsetInPlace(offset);
        End.Position.OffsetInPlace(offset);
    }

    void Line::ApplyScale(Vector2 scale)
    {
        // Start unnaffected, since it's the pivot
        End.Position.ScaleInPlace(scale);
    }

    void Line::ApplyRotation(float rotation)
    {
        // Set the 'End' vertex relative to (0,0) and rotate
        Vector2 diff = Start.Position;
        Vector2 rotator = End.Position - diff;
        rotator.RotateInPlace(rotation);

        // Restore original offset
        rotator += diff;
        End.Position = rotator;
    }

    void Line::ApplyTransform(const Transform2& tform)
    {
        ApplyScale(tform.Scale);
        ApplyRotation(tform.Rotation);
        ApplyOffset(tform.Position);
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