#include <rvi/vector2.hpp>

#include <cmath>
#include <rvi/transform2.hpp>

namespace rvi
{
    float vector2::magnitude() const noexcept
    {
        return std::sqrt(powf(x, 2) + powf(y, 2));
    }

    vector2 vector2::cross_product(vector2 other) const noexcept
    {
        return vector2(x * other.x, y * other.y);
    }

    void vector2::cross_product_in_place(vector2 other) noexcept
    {
        x *= other.x;
        y *= other.y;
    }

    vector2 vector2::offset(vector2 offset) const noexcept
    {
        return vector2(x + offset.x, y + offset.y);
    }

    void vector2::offset_in_place(vector2 offset) noexcept
    {
        x += offset.x;
        y += offset.y;
    }

    vector2 vector2::rotate(float angle) const noexcept
    {
        const float radAngle = rvi::math::deg2rad(angle);
        const float angleSin = std::sin(radAngle);
        const float angleCos = std::cos(radAngle);
	
        // [rx] = [cos(a) , -sin(a)][x]
        const float rx = (x * +angleCos) + (y * -angleSin);
	    // [ry] = [sin(a) ,  cos(a)][y]
        const float ry = (x * +angleSin) + (y * +angleCos);   

        return vector2(rx, ry);
    }

    void vector2::rotate_in_place(float angle) noexcept
    {
        const float radAngle = rvi::math::deg2rad(angle);
        const float angleSin = std::sin(radAngle);
        const float angleCos = std::cos(radAngle);
	
        const float aux_x = x;
        const float aux_y = y;

	    // [rx] = [cos(a) , -sin(a)][x]
        x = (aux_x * +angleCos) + (aux_y * -angleSin);
	    // [ry] = [sin(a) ,  cos(a)][y]
        y = (aux_x * +angleSin) + (aux_y * +angleCos);
    }

    vector2 vector2::reverse() const noexcept
    {
        return (*this) * -1;
    }

    void vector2::reverse_in_place() noexcept
    {
        *this *= -1;
    }

    vector2 vector2::invert() const noexcept
    {
        const float fx = (x == 0) ? 0 : (1 / x);
        const float fy = (y == 0) ? 0 : (1 / y);
        return vector2(fx, fy);
    }

    void vector2::invert_in_place() noexcept
    {
        x = (x == 0) ? 0 : (1 / x);
        y = (y == 0) ? 0 : (1 / y);
    }

    vector2 vector2::scale(vector2 scaleVec) const noexcept
    {
        return this->cross_product(scaleVec);
    }

    vector2 vector2::scale(float scale) const noexcept
    {
        return vector2(x * scale, y * scale);
    }

    void vector2::scale_in_place(float scale) noexcept
    {
        x *= scale;
        y *= scale;
    }

    void vector2::scale_in_place(vector2 scale) noexcept
    {
        cross_product_in_place(scale);
    }

    vector2 vector2::operator+(vector2 other) const noexcept
    {
        return vector2(x + other.x, y + other.y);
    }

    vector2 vector2::operator-(vector2 other) const noexcept
    {
        return vector2(x - other.x, y - other.y);
    }

    vector2 vector2::operator*(float other) const noexcept
    {
        return vector2(x * other, y * other);
    }

    vector2 vector2::operator*(vector2 other) const noexcept
    {
        return this->cross_product(other);
    }

    vector2 vector2::operator/(float other) const noexcept
    {
        return vector2(x / other, y / other);
    }

    vector2 vector2::operator/(vector2 other) const noexcept
    {
        return vector2((x / other.x), (y / other.y));
    }    

    void vector2::operator-=(vector2 other) noexcept
    {
        x -= other.x;
        y -= other.y;
    }

    void vector2::operator+=(vector2 other) noexcept
    {
        x += other.x;
        y += other.y;
    }

    void vector2::operator*=(float other) noexcept
    {
        x *= other;
        y *= other;
    }

    void vector2::operator*=(vector2 other) noexcept
    {
        this->cross_product_in_place(other);
    }

    void vector2::operator/=(float other) noexcept
    {
        x /= other;
        y /= other;
    }

    bool vector2::operator==(vector2 other) const
    {
        return math::fpcmp(x, other.x) && math::fpcmp(y, other.y);
    }

    bool vector2::operator!=(vector2 other) const
    {
        return !(math::fpcmp(x, other.x) && math::fpcmp(y, other.y));
    }

    std::string vector2::to_string() const
    {
        std::stringstream ss;
        ss << "[{X}:"
            << x
            << ",{Y}:"
            << y
            << "]";
        return ss.str();
    }
}