#include "Geometry.h"
#include "geometry/mesh/WireFrame.h"
#include "primitive/Rectangle.h"
#include "math/MathUtils.h"


namespace Geometry
{
	// Get a Wireframe from a Rectangle
	// Be aware that this does a memory allocation so 
	// the resulting WireFrame must be deallocated
	WireFrame* ConstrWireframeFromRect(const Rectangle& rect)
	{
		return MathUtils::CreateRectangleWireframe(rect.GetTop(), rect.GetBottom(), rect.GetLeft(), rect.GetRight());
	}

	// Get a Rectangle from a Wireframe
	// Be aware that this does a memory allocation so 
	// the resulting Rectangle must be deallocated
	Rectangle* ConstrRectFromWireframe(const WireFrame& wireframe)
	{
		//	3 ------------ 2
		//	|   		   |
		//	|			   |
		//	|			   |
		//  0 ------------ 1

		// TODO For now, we just support only one rectangle to be extracted from a Wireframe
		// In the future, a wireframe could store more than 2 polygons this resulting into
		// multiple rectangles being extracted.
		if(wireframe.GetPolyNr() != 2)
			return nullptr;

		const vec_2x pointBottomRight = wireframe.GetPolygonAtIndex(0)->vertex[1].normals;
		const vec_2x pointTopLeft = wireframe.GetPolygonAtIndex(1)->vertex[2].normals;
		
		return new Rectangle(pointTopLeft, pointBottomRight);
	}

	vec_2x CalculateRectPos(const Rectangle& rect)
	{
		vec_2x pos(0.0f, 0.0f);

		pos.elem[0] = rect.GetLeft() + ((rect.GetRight() - rect.GetLeft()) / 2.0f);
		pos.elem[1] = rect.GetTop() + ((rect.GetBottom() - rect.GetTop()) / 2.0f);

		return pos;
	}

	vec_2x CalculateRectDimensions(const Rectangle& rect)
	{
		// A rectangle can be positioned in multiple coordonate systems
		// In our case it can be in the OpenGL [-1, 1] system or in our game world [0 - 1600]

		float lenght = 0;
		float height = 0;
		
		// Calculate lenght
		if (rect.GetLeft() < 0.0f)
		{
			if (rect.GetRight() < 0.0f)
				lenght = (rect.GetLeft() - rect.GetRight()) * -1;
			else
				lenght = (rect.GetLeft() * -1) + rect.GetRight();
		}
		else
			lenght = rect.GetRight() - rect.GetLeft();

		// Calculate height
		if (rect.GetBottom() < 0.0f)
		{
			if (rect.GetTop() < 0.0f)
				height = (rect.GetBottom() - rect.GetTop()) * -1;
			else
				height = (rect.GetBottom() * -1) + rect.GetTop();
		}
		else
			height = rect.GetTop() - rect.GetBottom();

		return vec_2x(height, lenght);
	}
}