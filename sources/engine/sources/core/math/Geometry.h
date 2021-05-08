#pragma once
#include "math/Vector.h"

class WireFrame;
class Rectangle;

namespace Geometry
{
	// Get a Wireframe from a Rectangle
	// Be aware that this does a memory allocation so 
	// the resulting WireFrame must be deallocated
	WireFrame* ConstrWireframeFromRect(const Rectangle& rect);

	// Get a Rectangle from a Wireframe
	// Be aware that this does a memory allocation so 
	// the resulting Rectangle must be deallocated
	Rectangle* ConstrRectFromWireframe(const WireFrame& wireframe);

	vec_2x CalculateRectPos(const Rectangle& rect);

	// Given a rectangle we want to calculate the rect's height and lenght
	// the result will be put in a 2D vector:
	// index 0 - height
	// index 1 - lenght
	vec_2x CalculateRectDimensions(const Rectangle& rect);
}