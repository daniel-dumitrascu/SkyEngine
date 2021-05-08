#ifndef MATH_DEFINES
#define MATH_DEFINES

#include "Vector.h"

extern const float PI;
extern const float TWO_PI;          /* (PI * 2)   */
extern const float DIV_PI_180;      /* (PI / 180) */
extern const float DIV_180_PI;      /* (180 / PI) */

class WireFrame;

namespace MathUtils
{
	float ToRadian(const float degree);	
	float ToDegree(const float radian);

	// Computes the Top / Bottom / Left / Right coords
	vec_4x LineToRectangleCoord(const vec_2x& startLine, const vec_2x& endLine, const int thickness);

	// Create rectangle wireframe from the Top / Bottom / Left / Right coords
	WireFrame* CreateRectangleWireframe(const float top, const float bottom, const float left, const float right);
}

#endif