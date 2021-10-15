#pragma once
#include "math/Vector.h"
#include "math/Matrix.h"

class Camera
{
public:
	Camera(vec_2x& resolution, vec_3x& position, vec_3x& rotation);
	~Camera() {};

	void SetPosition(const vec_3x& position);

	const mat_4x& BuildViewMatrix();

private:
	mat_4x word_mat;
	mat_4x view_mat;

	vec_3x camera_position;
	vec_3x camera_rotation;
	vec_2x camera_resolution;
};