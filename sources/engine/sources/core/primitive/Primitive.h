#ifndef GAME_PRIMITIVE
#define GAME_PRIMITIVE

#include "math/Vector.h"
#include "geometry/mesh/WireFrame.h"
#include "math/Matrix.h"


class Primitive
{
	public:

		Primitive();
		Primitive(const Primitive& copy);
		virtual ~Primitive() { };
};


#endif