#include "Plane.h"
#include <stdio.h>
#include <math.h>

//TODO: netestat
void plane::BuildPlaneFromPoly(plan_x& R, const poly_x_trig& P)
{
	GetPolyNormal(R.plane_normal, P);

	// Using a point on the polygon (vertex) and the normal we can calculate the distance to the plane
	R.dist_plane = GetOriginPlaneDist(P.vertex[0], R);
	//directX page 59
}

/***********************************************************************************************/
/***********************************************************************************************/
//TODO: netestat
void plane::GetPolyNormal(vec_3x& Normal, const poly_x_trig& P)
{
	vec_3x Edge1, Edge2, Normal_temp;

	SetVector(Normal_temp, Normal);

	// Using the edges of the poligon we can calculate the normal by using the cross product
	Subtraction(Edge1, P.vertex[1], P.vertex[0]);
	Subtraction(Edge2, P.vertex[2], P.vertex[0]);

	CrossProduct(Normal_temp, Edge1, Edge2 );
	Normalization(Normal, Normal_temp);
}

/***********************************************************************************************/
/***********************************************************************************************/
//TODO: netestat
//TODO: we may need to know if the dist is pozitive or negative to know if the 
float plane::GetPointPlaneDist(const float plane_orig_dist, const vec_3x& point)
{
	// Make de magnitude of the vector
	const float length = Magnitude(point);

	// The distance from the origin to the plane minus the length of the vector (point)
	return fabs(plane_orig_dist - length);
}

/***********************************************************************************************/
/***********************************************************************************************/
//TODO: netestat
float plane::GetOriginPlaneDist(const vec_3x point_on_plan, const plan_x plane)
{
	return DotProduct(point_on_plan, plane.plane_normal);
}