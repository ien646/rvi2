#include "vector2.h"
#include "transform2.h"
#include <cmath>

namespace rvi
{
	Vector2::Vector2(float x, float y) noexcept
	{
		X = x;
		Y = y;
	}

	float Vector2::Magnitude() const noexcept
	{
		return std::sqrtf(powf(X, 2) + powf(Y, 2));
	}

	Vector2 Vector2::CrossProduct(Vector2 other) const noexcept
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	void Vector2::CrossProductInPlace(Vector2 other) noexcept
	{
		X *= other.X;
		Y *= other.Y;
	}

	Vector2 Vector2::Offset(Vector2 offset) const noexcept
	{
		return Vector2(X + offset.X, Y + offset.Y);
	}

	void Vector2::OffsetInPlace(Vector2 offset) noexcept
	{
		X += offset.X;
		Y += offset.Y;
	}

	Vector2 Vector2::Rotate(float angle) const noexcept
	{
		const float angleSin = std::sin(angle);
		const float angleCos = std::cos(angle);

		const float rx = (X * +angleCos) + (Y * -angleSin);   // [rx] = [cos(a) , -sin(a)][x]
		const float ry = (X * +angleSin) + (Y * +angleCos);   // [ry] = [sin(a) ,  cos(a)][y]

		return Vector2(rx, ry);
	}

	void Vector2::RotateInPlace(float angle) noexcept
	{
		const float angleSin = std::sin(angle);
		const float angleCos = std::cos(angle);

		X = (X * + angleCos) + (Y * - angleSin);   // [rx] = [cos(a) , -sin(a)][x]
		Y = (X * + angleSin) + (Y * + angleCos);   // [ry] = [sin(a) ,  cos(a)][y]
	}

	Vector2 Vector2::Reverse() const noexcept
	{
		return (*this) * -1;
	}

	void Vector2::ReverseInPlace() noexcept
	{
		*this *= -1;
	}

	Vector2 Vector2::Inverse() const noexcept
	{
		return Vector2(1 / X, 1 / Y);
	}

	void Vector2::InvertInPlace() noexcept
	{
		X = 1 / X;
		Y = 1 / Y;
	}

	Vector2 Vector2::Scale(Vector2 scaleVec) const noexcept
	{
		return this->CrossProduct(scaleVec);
	}	

	Vector2 Vector2::Scale(float scale) const noexcept
	{
		return Vector2(X * scale, Y * scale);
	}

	void Vector2::ScaleInPlace(float scale) noexcept
	{
		X *= scale;
		Y *= scale;
	}

	void Vector2::ScaleInPlace(Vector2 scale) noexcept
	{
		X *= scale.X;
		Y *= scale.Y;
	}

	void Vector2::ApplyTransform(const Transform2& tform) noexcept
	{
		OffsetInPlace(tform.Position);
		RotateInPlace(tform.Rotation);
		ScaleInPlace(tform.Scale);
	}

	Vector2 Vector2::operator+(Vector2 other) const noexcept
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 Vector2::operator-(Vector2 other) const noexcept
	{
		return Vector2(X - other.X, Y - other.Y);
	}

	Vector2 Vector2::operator*(float other) const noexcept
	{
		return Vector2(X * other, Y * other);
	}

	Vector2 Vector2::operator*(Vector2 other) const noexcept
	{
		return this->CrossProduct(other);
	}

	Vector2 Vector2::operator/(float other) const noexcept
	{
		return Vector2(X / other, Y / other);
	}

	Vector2 Vector2::operator/(Vector2 other) const noexcept
	{
		return Vector2((X / other.X), (Y / other.Y));
	}

	void Vector2::operator-=(Vector2 other) noexcept
	{
		X -= other.X;
		Y -= other.Y;
	}

	void Vector2::operator+=(Vector2 other) noexcept
	{
		X += other.X;
		Y += other.Y;
	}	

	void Vector2::operator*=(float other) noexcept
	{
		X *= other;
		Y *= other;
	}

	void Vector2::operator*=(Vector2 other) noexcept
	{
		this->CrossProductInPlace(other);
	}

	void Vector2::operator/=(float other) noexcept
	{
		X /= other;
		Y /= other;
	}

	void Vector2::operator/=(Vector2 other) noexcept
	{
		X /= other.X;
		Y /= other.Y;
	}
}