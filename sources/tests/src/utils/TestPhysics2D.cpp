#include "TestPhysics2D.h"
#include "utils/Physics2D.h"
#include <assert.h>

void TestPhysics2D::TestCollisionDetectionAABB()
{
	// Colisiune dreapta jos
	Rectangle a = ConstrRectangle(2, 5, 5, 3);
	Rectangle b = ConstrRectangle(4, 4, 6, 2);

	bool result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);
	
	// Colisiune dreapta sus
	a = ConstrRectangle(3, 3, 5, 1);
	b = ConstrRectangle(4, 4.5, 7, 2.5);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune stanga jos
	a = ConstrRectangle(4, 4.5, 7, 2.5);
	b = ConstrRectangle(3, 3, 5, 1);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune stanga sus
	a = ConstrRectangle(4, 4, 6, 2);
	b = ConstrRectangle(2, 5, 5, 3);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune dreapta total
	a = ConstrRectangle(2, 2, 4, 1);
	b = ConstrRectangle(3, 2.5, 5, 0.5);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune stanga total
	a = ConstrRectangle(3, 3, 5, 2);
	b = ConstrRectangle(2, 3.5, 4, 1.5);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune stanga partial
	a = ConstrRectangle(3, 2.5, 5, 0.5);
	b = ConstrRectangle(2, 2, 4, 1);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune dreapta partial
	a = ConstrRectangle(2, 3.5, 4, 1.5);
	b = ConstrRectangle(3, 3, 5, 2);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune top total
	a = ConstrRectangle(1.5, 2, 2.5, 1);
	b = ConstrRectangle(1, 2.5, 3, 1.5);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune bottom total
	a = ConstrRectangle(1.5, 3, 2.5, 2);
	b = ConstrRectangle(1, 2.5, 3, 1.5);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune bottom partial
	a = ConstrRectangle(1, 2.5, 3, 1.5);
	b = ConstrRectangle(1.5, 2, 2.5, 1);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune top partial
	a = ConstrRectangle(1, 2.5, 3, 1.5);
	b = ConstrRectangle(1.5, 3, 2.5, 2);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Doar overlap pe axa x (fara colisiune)
	a = ConstrRectangle(1, 4, 2, 3);
	b = ConstrRectangle(1.5, 2, 2.5, 1);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == false);

	// Doar overlap pe axa y (fara colisiune)
	a = ConstrRectangle(1, 2, 2, 1);
	b = ConstrRectangle(3, 2, 4, 1);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == false);

	// Colisiune toata, dreptunghiul A este complet in dreptunghiul B
	a = ConstrRectangle(2, 3, 3, 2);
	b = ConstrRectangle(1, 4, 4, 1);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);

	// Colisiune toata, dreptunghiul B este complet in dreptunghiul A
	a = ConstrRectangle(1, 4, 4, 1);
	b = ConstrRectangle(2, 3, 3, 2);

	result = Physics2D::CollisionDetectionAABB(a, b);
	assert(result == true);
}


Rectangle TestPhysics2D::ConstrRectangle(float left, float top, float right, float bottom)
{
	const vec_2x pointLeftTop(left, top);
	const vec_2x pointRightBottom(right, bottom);
	return Rectangle(pointLeftTop, pointRightBottom);
}
