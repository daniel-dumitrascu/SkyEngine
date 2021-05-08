#ifndef PRIMITIVE_LINE_H
#define PRIMITIVE_LINE_H

#include "Primitive.h"


class Line : public Primitive
{
	public:

		Line(vec_2x& startPoint, vec_2x& endPoint, int thickness);
		Line(const Line& copy);
		virtual ~Line() {};

		WireFrame* GetConstructedWireFrame();
		float GetThickness() { return m_thickness;  }

	private:

		vec_2x m_startLine;
		vec_2x m_endLine;
		float  m_thickness;
};

#endif