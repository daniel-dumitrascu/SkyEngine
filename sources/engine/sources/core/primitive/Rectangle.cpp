#include "Rectangle.h"
#include "../math/MathUtils.h"

Rectangle::Rectangle(const vec_2x& pointLeftTop, const vec_2x& pointRightBottom) : Primitive()
{
	vector::vector_2x::SetVector(m_pointLeftTop, pointLeftTop);
	vector::vector_2x::SetVector(m_pointRightBottom, pointRightBottom);
}

Rectangle::Rectangle(const Rectangle& copy)
{
	vector::vector_2x::SetVector(m_pointLeftTop, copy.m_pointLeftTop);
	vector::vector_2x::SetVector(m_pointRightBottom, copy.m_pointRightBottom);
}