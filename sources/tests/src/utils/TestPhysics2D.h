#pragma once
#include "primitive/Rectangle.h"

class TestPhysics2D
{
public:

	void TestCollisionDetectionAABB();
	

private:

	Rectangle ConstrRectangle(float left, float top, float right, float bottom);
};