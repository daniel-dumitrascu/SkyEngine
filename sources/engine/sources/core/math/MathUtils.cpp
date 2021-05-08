#include "MathUtils.h"
#include "geometry/mesh/WireFrame.h"

const float PI     = 3.141592654f;
const float TWO_PI = 6.283185307f;        
const float DIV_PI_180 = 0.017453292f;   
const float DIV_180_PI = 57.295779505f;  

namespace MathUtils
{
	float ToRadian(const float degree)
	{
		return degree * DIV_PI_180;
	}
	
	float ToDegree(const float radian)
	{
		return radian * DIV_180_PI; 
	}	

	vec_4x LineToRectangleCoord(const vec_2x& startLine, const vec_2x& endLine, const int thickness)
	{
		vec_2x normLineVector;

		// Move the line vector to origin
		vector::vector_2x::Subtraction(normLineVector, endLine, startLine);

		// Normalize the vector
		vector::vector_2x::Normalization(normLineVector, normLineVector);

		// Get the perpendicular vector from it
		vector::vector_2x::Perpendicular(normLineVector, normLineVector);

		// Set the thickness 
		// Default thickness for one side of the line rectangle 
		// 0.5f + 0.5f = 1 pixel thickness						
		float lineHalfThickness = thickness > 1 ? thickness / 2 : 0.5f;

		// Add the thickness
		normLineVector.elem[0] *= lineHalfThickness;
		normLineVector.elem[1] *= lineHalfThickness;

		vec_4x coord;

		// Compute the top, bottom, left and right params, counter-clockwise
		coord.elem[0] = endLine.elem[1] + (-normLineVector.elem[1]);	// Top
		coord.elem[1] = startLine.elem[1] + normLineVector.elem[1];		// Bottom
		coord.elem[2] = endLine.elem[0] + (-normLineVector.elem[0]);	// Left
		coord.elem[3] = startLine.elem[0] + normLineVector.elem[0];		// Right

		return coord;
	}

	//TODO this method must be optimized 
	WireFrame* CreateRectangleWireframe(const float top, const float bottom, const float left, const float right)
	{
		//	3 ------------ 2
		//	|   		   |
		//	|			   |
		//	|			   |
		//  0 ------------ 1

		WireFrame* wireframe = new WireFrame;

		wireframe->SetNormalsNr(4);
		wireframe->SetPolyNr(2);

		std::vector<vec_2x> normals;
		vec_3x normal_idx;
		Polygon polygon;

		normals.push_back(vec_2x(left, bottom));	// 0 point
		normals.push_back(vec_2x(right, bottom));	// 1 point
		normals.push_back(vec_2x(right, top));		// 2 point
		normals.push_back(vec_2x(left, top));		// 3 point

		normal_idx.elem[0] = 0;
		normal_idx.elem[1] = 1;
		normal_idx.elem[2] = 2;

		for (int i = 0; i < 3; ++i)
		{
			polygon.vertex[i].normals.elem[0] = normals[normal_idx.elem[i]].elem[0];
			polygon.vertex[i].normals.elem[1] = normals[normal_idx.elem[i]].elem[1];
		}

		wireframe->AddPolygon(polygon);

		normal_idx.elem[0] = 0;
		normal_idx.elem[1] = 2;
		normal_idx.elem[2] = 3;

		for (int i = 0; i < 3; ++i)
		{
			polygon.vertex[i].normals.elem[0] = normals[normal_idx.elem[i]].elem[0];
			polygon.vertex[i].normals.elem[1] = normals[normal_idx.elem[i]].elem[1];
		}

		wireframe->AddPolygon(polygon);

		return wireframe;
	}
}
