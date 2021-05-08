#ifndef PRIMITIVE_RECTANGLE_H
#define PRIMITIVE_RECTANGLE_H

#include "Primitive.h"


class Rectangle : public Primitive
{
	public:

		Rectangle(const vec_2x& pointLeftTop, const vec_2x& pointRightBottom);
		Rectangle(const Rectangle& copy);
		virtual ~Rectangle() {};

		float GetTop() const { return m_pointLeftTop.elem[1]; }
		float GetBottom() const { return m_pointRightBottom.elem[1]; }
		float GetLeft() const { return m_pointLeftTop.elem[0]; }
		float GetRight() const { return m_pointRightBottom.elem[0]; }

	private:

		vec_2x m_pointLeftTop;
		vec_2x m_pointRightBottom;
};

#endif