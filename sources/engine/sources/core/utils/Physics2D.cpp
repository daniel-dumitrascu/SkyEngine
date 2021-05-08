#include "Physics2D.h"

namespace Physics2D
{
	//TODO to test
	bool CollisionDetectionAABB(const Rectangle& A, const Rectangle& B)
	{
		bool isColliding = false;

		//The 'x' values overlap if A's left value is less than B's right AND A's right value is greater than B's left
		//The 'y' values overlap if A's bottom value is less than B's top AND A's top value is greater than B's bottom

		// X axis
		if (A.GetLeft() < B.GetRight() && A.GetRight() > B.GetLeft())
		{
			// Y axis
			if (A.GetBottom() < B.GetTop() && A.GetTop() > B.GetBottom())
			{
				isColliding = true;
			}
		}

		return isColliding;
	}
}