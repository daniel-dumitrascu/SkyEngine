#include "Line.h"
#include "../math/MathUtils.h"
#include "Rectangle.h"



Line::Line(vec_2x& startPoint, 
			vec_2x& endPoint, 
			int thickness) : Primitive()
{
	vector::vector_2x::SetVector(m_startLine, startPoint);
	vector::vector_2x::SetVector(m_endLine, endPoint);
	m_thickness = thickness;
}

Line::Line(const Line& copy)
{
	vector::vector_2x::SetVector(m_startLine, copy.m_startLine);
	vector::vector_2x::SetVector(m_endLine, copy.m_endLine);
	m_thickness = copy.m_thickness;
}

WireFrame* Line::GetConstructedWireFrame()
{
	vec_4x rectangleCoord = MathUtils::LineToRectangleCoord(m_startLine, m_endLine, m_thickness);
	return MathUtils::CreateRectangleWireframe(rectangleCoord.elem[0], rectangleCoord.elem[1], rectangleCoord.elem[2], rectangleCoord.elem[3]);
}