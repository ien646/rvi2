/* FILE: transform2.h */
#pragma once

#include "vector2.h"

namespace rvi
{
	class Transform2
	{
	public:
		Vector2 Position;
		Vector2 Scale;
		FLOAT Rotation = 0.0F;
		
		Transform2() noexcept { }
		Transform2(Vector2 pos, Vector2 scale, FLOAT rot);
	};
}