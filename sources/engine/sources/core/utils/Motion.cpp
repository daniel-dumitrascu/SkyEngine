#include "Motion.h"

namespace Motion
{
	float MotionInterpolation(float goal, float current, float deltaTime)
	{
		float diff = goal - current;

		if (diff > deltaTime)
			return current + deltaTime;
		if (diff < -deltaTime)
			return current - deltaTime;

		return goal;
	}
}
