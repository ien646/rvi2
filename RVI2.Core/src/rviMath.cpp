#include "rviMath.h"

namespace rvi
{
	float Math::Deg2Rad(float angleDeg)
	{
		return angleDeg * PI / 180;
	}

	float Math::Rad2Deg(float angleRad)
	{
		return angleRad * 180 / PI;
	}

	Math::Matrix2x2 Math::Get2DRotationMatrix(float angle)
	{
		float angleRadians = Deg2Rad(angle);
		return Matrix2x2
		{
			std::cos(angleRadians), -std::sin(angleRadians),
			std::sin(angleRadians),  std::cos(angleRadians)
		};
	}
}