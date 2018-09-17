/* FILE: Vector2.h */
#pragma once

#include "rviTypes.h"

namespace rvi
{
	class Transform2;

	class Vector2
	{
	public:
		float X = 0.0F;
		float Y = 0.0F;
		
		constexpr Vector2() noexcept { }

		Vector2(float x, float y) noexcept;
		
		float Magnitude() const;
		
		Vector2 CrossProduct(Vector2 other) const;
		void CrossProductInPlace(Vector2 other);

		Vector2 Offset(Vector2 offset) const;
		void OffsetInPlace(Vector2 offset);

		Vector2 Rotate(float angle) const;
		void RotateInPlace(float angle);

		Vector2 Reverse() const;
		void ReverseInPlace();

		Vector2 Inverse() const;
		void InvertInPlace();

		Vector2 Scale(float scale) const;
		Vector2 Scale(Vector2 scaleVec) const;
		void ScaleInPlace(float scale);
		void ScaleInPlace(Vector2 scale);

		void ApplyTransform(const Transform2& tform);
		
		Vector2 operator+(Vector2 other) const;		
		Vector2 operator-(Vector2 other) const;		
		Vector2 operator*(float other) const;	
		Vector2 operator*(Vector2 other) const;
		Vector2 operator/(float other) const;
		Vector2 operator/(Vector2 other) const;
		
		void operator+=(Vector2 other);		
		void operator-=(Vector2 other);		
		void operator*=(float other);
		void operator*=(Vector2 other);
		void operator/=(float other);
		void operator/=(Vector2 other);
	};
}