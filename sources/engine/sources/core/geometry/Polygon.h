#ifndef VERTEX_H
#define VERTEX_H

#include "math/Vector.h"

const unsigned int TRIANGLE_FACE = 3;

struct Vertex
{
	vec_2x normals;    /* Vertex position in normalized coor. */
	vec_2x texture;    /* 2D texture coordonates */
};

struct Polygon
{
	Vertex vertex[TRIANGLE_FACE];
};

#endif