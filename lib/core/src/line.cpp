#include "line.hpp"

namespace rvi
{
    line::line(const vertex& start, const vertex& end) noexcept
        : start(start)
        , end(end)
    { }

    line::line(vertex&& start, vertex&& end) noexcept
        : start(std::move(start))
        , end(std::move(end))
    { }
    
    void line::apply_position(vector2 offset)
    {
        start.position.offset_in_place(offset);
        end.position.offset_in_place(offset);
    }

    void line::apply_scale(vector2 scale)
    {
        // Start unnaffected, since it's the pivot
        end.position.scale_in_place(scale);
    }

    void line::apply_rotation(float rotation)
    {
        // Set the 'End' vertex relative to (0,0) and rotate
        vector2 diff = start.position;
        vector2 rotator = end.position - diff;
        rotator.rotate_in_place(rotation);

        // Restore original offset
        rotator += diff;
        end.position = rotator;
    }

    void line::apply_transform(const transform2& tform)
    {
        apply_scale(tform.scale);
        apply_rotation(tform.rotation);
        apply_position(tform.position);
    }

    bool line::operator==(line other) const noexcept
    {
        return (start == other.start) && (end == other.end);
    }

    bool line::operator!=(line other) const noexcept
    {
        return (start != other.start) || (end != other.end);
    }
}