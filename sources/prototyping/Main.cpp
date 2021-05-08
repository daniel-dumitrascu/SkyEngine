#include <iostream>
#include "utils/UniqueGenerator.h"
#include "geometry/mesh/WireFrame.h"
#include "primitive/Rectangle.h"
#include "utils/Geometry.h"

#include <math.h>

void TestUniqueGenerator();
void TestWireframeRectConstr();


int main()
{
	int VIRTUAL_WORLD_MULTIPLIER = 10;
	float T = 40;
	float B = 50.01;
	float L = 40;
	float R = 50;


	float tempObjectTopGridIndex = T / (float)VIRTUAL_WORLD_MULTIPLIER;
	float tempObjectBottomGridIndex = B / (float)VIRTUAL_WORLD_MULTIPLIER;
	float tempObjectLeftGridIndex = L / (float)VIRTUAL_WORLD_MULTIPLIER;
	float tempObjectRightGridIndex = R / (float)VIRTUAL_WORLD_MULTIPLIER;


	int objectTopGridIndex = (int)tempObjectTopGridIndex + 1;
	int objectLeftGridIndex = (int)tempObjectLeftGridIndex + 1;
	int objectBottomGridIndex = (int)tempObjectBottomGridIndex;
	int objectRightGridIndex = (int)tempObjectRightGridIndex;


	if(std::fmod(B, (float)VIRTUAL_WORLD_MULTIPLIER) > 0.0f)
		++objectBottomGridIndex;

	if (std::fmod(R, (float)VIRTUAL_WORLD_MULTIPLIER) > 0.0f)
		++objectRightGridIndex;
}

void TestWireframeRectConstr()
{
	WireFrame* wireframe_original = new WireFrame();

	// Player wireframe data
	wireframe_original->SetNormalsNr(4);
	wireframe_original->SetTexcoordNr(4);
	wireframe_original->SetPolyNr(2);

	Polygon poly1;
	poly1.vertex[0].normals.elem[0] = -0.562500000;
	poly1.vertex[0].normals.elem[1] = -0.826799989;
	poly1.vertex[1].normals.elem[0] = 0.562500000;
	poly1.vertex[1].normals.elem[1] = -0.826799989;
	poly1.vertex[2].normals.elem[0] = 0.562500000;
	poly1.vertex[2].normals.elem[1] = 0.826799989;
	wireframe_original->AddPolygon(poly1);

	Polygon poly2;
	poly2.vertex[0].normals.elem[0] = -0.562500000;
	poly2.vertex[0].normals.elem[1] = -0.826799989;
	poly2.vertex[1].normals.elem[0] = 0.562500000;
	poly2.vertex[1].normals.elem[1] = 0.826799989;
	poly2.vertex[2].normals.elem[0] = -0.562500000;
	poly2.vertex[2].normals.elem[1] = 0.826799989;
	wireframe_original->AddPolygon(poly2);

	Rectangle* rect = Geometry::ConstrRectFromWireframe(*wireframe_original);

	WireFrame* wireframe_constr = Geometry::ConstrWireframeFromRect(*rect);

	//wireframe_original si wireframe_constr trebuie sa aibe valori egale
}

void TestUniqueGenerator()
{
	UniqueGenerator uniqueGenerator;

	for (int i = 0; i < 10; ++i)
	{
		std::cout << "generating the id number: " << uniqueGenerator.GenerateUniqueID() << std::endl;
	}

	uniqueGenerator.RemoveID(7);
	uniqueGenerator.RemoveID(1);
	uniqueGenerator.RemoveID(3);

	std::cout << "generating id: " << uniqueGenerator.GenerateUniqueID() << std::endl;
	std::cout << "generating id: " << uniqueGenerator.GenerateUniqueID() << std::endl;
	std::cout << "generating id: " << uniqueGenerator.GenerateUniqueID() << std::endl;
	std::cout << "generating id: " << uniqueGenerator.GenerateUniqueID() << std::endl;
}