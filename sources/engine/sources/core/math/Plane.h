#ifndef PLANE_H
#define PLANE_H

#include "Vector.h"


#define    LINE        2
#define    TRIANGLE    3
#define    RECTANGLE   4

//TODO: netestat
using namespace vector::vector_3x;
using namespace vector::vector_4x;


// The plane structure
struct plan_x
{
	float    dist_plane;
	vec_3x   plane_normal;
};


// The polygon structures
/*********************************************/
struct poly_x_line
{
	vec_3x   vertex[LINE]; 
};


struct poly_x_trig
{
	vec_3x   vertex[TRIANGLE]; 
};


struct poly_x_rect
{
	vec_3x   vertex[RECTANGLE];
};
/**********************************************/




namespace plane
{
    // Build a plane from a given polygon
    void BuildPlaneFromPoly(plan_x& R, const poly_x_trig& P);

	// Computes the normal of a polygon
	void GetPolyNormal(vec_3x& Normal, const poly_x_trig& P);

	// Computes the distance from a polygon to a point in 3D space
	float GetPointPlaneDist(const float plane_orig_dist, const vec_3x& point);

	// Computes the distance from the origin to the plane
	float GetOriginPlaneDist(const vec_3x point_on_plan, const plan_x plane);
}


#endif