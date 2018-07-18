#include "vector2.h"
#include <cmath>

namespace rvi
{
	Vector2::Vector2(FLOAT x, FLOAT y) noexcept
	{
		X = x;
		Y = y;
	}

	FLOAT Vector2::Magnitude() const
	{
		return std::sqrtf(powf(X, 2) + powf(Y, 2));
	}

	Vector2 Vector2::CrossProduct(Vector2 other)
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	void Vector2::CrossProductInPlace(Vector2 other)
	{
		X *= other.X;
		Y *= other.Y;
	}

	Vector2 Vector2::Offset(Vector2 offset)
	{
		return Vector2(X + offset.X, Y + offset.Y);
	}

	void Vector2::OffsetInPlace(Vector2 offset)
	{
		X += offset.X;
		Y += offset.Y;
	}

	Vector2 Vector2::Rotate(FLOAT angle)
	{
		FLOAT angleSin = std::sin(angle);
		FLOAT angleCos = std::cos(angle);

		FLOAT rx = (X * +angleCos) + (Y * -angleSin);   // [rx] = [cos(a) , -sin(a)][x]
		FLOAT ry = (X * +angleSin) + (Y * +angleCos);   // [ry] = [sin(a) ,  cos(a)][y]

		return Vector2(rx, ry);
	}

	void Vector2::RotateInPlace(FLOAT angle)
	{
		FLOAT angleSin = std::sin(angle);
		FLOAT angleCos = std::cos(angle);

		X = (X * +angleCos) + (Y * -angleSin);   // [rx] = [cos(a) , -sin(a)][x]
		Y = (X * +angleSin) + (Y * +angleCos);   // [ry] = [sin(a) ,  cos(a)][y]
	}

	Vector2 Vector2::Scale(Vector2 scaleVec)
	{
		return this->CrossProduct(scaleVec);
	}	

	rvi::Vector2 Vector2::Scale(FLOAT scale)
	{
		return Vector2(X * scale, Y * scale);
	}

	void Vector2::ScaleInPlace(FLOAT scale)
	{
		X *= scale;
		Y *= scale;
	}

	void Vector2::ScaleInPlace(Vector2 scale)
	{
		X *= scale.X;
		Y *= scale.Y;
	}

	Vector2 Vector2::ApplyTransform(const Transform2& transform)
	{
		Vector2 result = *this;

		result.ScaleInPlace(transform.Scale);
		result.RotateInPlace(transform.Rotation);
		result.OffsetInPlace(transform.Position);

		return result;
	}

	Vector2 Vector2::ApplyTransformInPlace(const Transform2& transform)
	{
		ScaleInPlace(transform.Scale);
		RotateInPlace(transform.Rotation);
		OffsetInPlace(transform.Position);
	}

	Vector2 Vector2::operator+(Vector2 other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 Vector2::operator-(Vector2 other) const
	{
		return Vector2(X - other.X, Y - other.Y);
	}

	Vector2 Vector2::operator*(FLOAT other) const
	{
		return Vector2(X * other, Y * other);
	}

	Vector2 Vector2::operator/(FLOAT other) const
	{
		return Vector2(X / other, Y / other);
	}

	void Vector2::operator/=(FLOAT other)
	{
		X /= other;
		Y /= other;
	}

	void Vector2::operator*=(FLOAT other)
	{
		X *= other;
		Y *= other;
	}

	void Vector2::operator-=(Vector2 other)
	{
		X -= other.X;
		Y -= other.Y;
	}

	void Vector2::operator+=(Vector2 other)
	{
		X += other.X;
		Y += other.Y;
	}	
}