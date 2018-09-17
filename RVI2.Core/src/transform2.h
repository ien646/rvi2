/* FILE: transform2.h */
#pragma once

#include "vector2.h"
#include "rviMath.h"
#include "line.h"

#include <vector>

// -- SSE - NEON -----------------
 #ifdef X86
 #include <pmmintrin.h>
 #elif ARM
 #include <arm_neon.h>
 #endif

namespace rvi
{
	class Transform2
	{
	public:
		Vector2 Position;
		Vector2 Scale;
		float Rotation = 0.0F;
		
		Transform2() noexcept { }
		Transform2(Vector2 pos, Vector2 scale, float rot);

		void ApplyTo(std::vector<Line>& vecs) const;

		Transform2 Merge(const Transform2& other);
	};
}