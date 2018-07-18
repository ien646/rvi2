/* FILE: Vector2.h */
#pragma once

#include "rviTypes.h"
#include "transform2.h"

namespace rvi
{
	class Vector2
	{
	public:
		FLOAT X = 0.0F;
		FLOAT Y = 0.0F;
		
		constexpr Vector2() noexcept { }

		Vector2(FLOAT x, FLOAT y) noexcept;
		
		FLOAT Magnitude() const;
		
		Vector2 CrossProduct(Vector2 other);

		void CrossProductInPlace(Vector2 other);

		Vector2 Offset(Vector2 offset);

		void OffsetInPlace(Vector2 offset);

		Vector2 Rotate(FLOAT angle);

		void RotateInPlace(FLOAT angle);

		Vector2 Scale(FLOAT scale);

		Vector2 Scale(Vector2 scaleVec);

		void ScaleInPlace(FLOAT scale);

		void ScaleInPlace(Vector2 scale);

		Vector2 ApplyTransform(const Transform2& transform);

		Vector2 ApplyTransformInPlace(const Transform2& transform);
		
		Vector2 operator+(Vector2 other) const;
		
		Vector2 operator-(Vector2 other) const;
		
		Vector2 operator*(FLOAT other) const;
		
		Vector2 operator/(FLOAT other) const;
		
		void operator+=(Vector2 other);
		
		void operator-=(Vector2 other);
		
		void operator*=(FLOAT other);
		
		void operator/=(FLOAT other);
	};
}