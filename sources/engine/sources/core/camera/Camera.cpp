#include "Camera.h"
#include <algorithm>
#include <iterator>


Camera::Camera(vec_2x& resolution, vec_3x& position, vec_3x& rotation)
{
	std::copy(std::begin(resolution.elem), std::end(resolution.elem), std::begin(camera_resolution.elem));
	std::copy(std::begin(position.elem), std::end(position.elem), std::begin(camera_position.elem));
	std::copy(std::begin(rotation.elem), std::end(rotation.elem), std::begin(camera_rotation.elem));

	matrix::matrix_4x::SetIdentity(word_mat);
	matrix::matrix_4x::SetIdentity(view_mat);
}

void Camera::SetPosition(const vec_3x& position)
{
	std::copy(std::begin(position.elem), std::end(position.elem), std::begin(camera_position.elem));

	//TODO here we can also rebuild the view matrix and in GetViewMatrix() we just return the matrix
}

const mat_4x& Camera::BuildViewMatrix()
{
	// Constructing the world matrix
	matrix::game_matrix::SetWorldScale(word_mat, 1.0); //TODO setting another value then 1 will not work
	matrix::game_matrix::SetWorldPosition(word_mat, camera_position);
	//TODO rotation

	// Construct view matrix
	matrix::game_matrix::BuildViewMatrix(view_mat, word_mat);

	return view_mat;


	//game_matrix::BuildWorldMat(*word_mat, cam_rot.x, cam_rot.y, cam_rot.z, 1.0, cam_pos.x, cam_pos.y, cam_pos.z);
	//game_matrix::BuildViewMat(*view_mat, *word_mat);
}