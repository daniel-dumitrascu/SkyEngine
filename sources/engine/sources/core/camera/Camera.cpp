#include "Camera.h"
#include "global/GlobalData.h"
#include <algorithm>
#include <iterator>


Camera::Camera(const vec_3x& position, const vec_3x& rotation) : cameraCenterOnX(0.0f), cameraCenterOnY(0.0f)
{
	std::copy(std::begin(position.elem), std::end(position.elem), std::begin(camera_position.elem));
	std::copy(std::begin(rotation.elem), std::end(rotation.elem), std::begin(camera_rotation.elem));

	matrix::matrix_4x::SetIdentity(word_mat);
	matrix::matrix_4x::SetIdentity(view_mat);

	buildMatrixPtr = &Camera::BuildViewMatrixWithoutAttachedObject;

	// Calculate the resolution
	cameraCenterOnX = (WINDOWS_ASP_RATIO_X * WINDOWS_SCREEN_MULTIPLIER) / 2.0f;
	cameraCenterOnY = (WINDOWS_ASP_RATIO_Y * WINDOWS_SCREEN_MULTIPLIER) / 2.0f;
}

void Camera::SetPosition(const vec_3x& position)
{
	std::copy(std::begin(position.elem), std::end(position.elem), std::begin(camera_position.elem));
	CenterCamera(camera_position.elem[0], camera_position.elem[1]);
}

void Camera::SetRotation(const vec_3x& rotation)
{
	std::copy(std::begin(rotation.elem), std::end(rotation.elem), std::begin(camera_rotation.elem));
}

void Camera::AttachCameraToObject(GameObject* obj) 
{
	if (obj)
	{
		attachedObject = obj;
		buildMatrixPtr = &Camera::BuildViewMatrixUsingAttachedObject;
	}
}

void Camera::DetachCameraFromObject()
{ 
	attachedObject = nullptr; 
	buildMatrixPtr = &Camera::BuildViewMatrixWithoutAttachedObject;
}

const mat_4x& Camera::GetViewMatrix()
{
	return (this->*buildMatrixPtr)();
}

const mat_4x& Camera::BuildViewMatrixUsingAttachedObject()
{
	vec_2x pos = attachedObject->GetPosition();
	CenterCamera(pos.elem[0], pos.elem[1]);

	//TODO - we use a hardcoded value for the scaling and not the one from the object because otherwise the objects will disappear
	return BuildViewMatrix(1.0f, pos.elem[0], pos.elem[1], 0.0f);
}

const mat_4x& Camera::BuildViewMatrixWithoutAttachedObject()
{
	return BuildViewMatrix(1.0f, camera_position.elem[0], camera_position.elem[1], camera_position.elem[2]);
}

const mat_4x& Camera::BuildViewMatrix(const float scale, const float posX, const float posY, const float posZ)
{
	// Constructing the world matrix
	matrix::game_matrix::SetWorldScale(word_mat, scale);
	matrix::game_matrix::SetWorldPosition(word_mat, posX, posY, posZ);
	//TODO rotation - after rotation is implemented, call BuildWorldMatrix() here

	// Construct the view matrix
	matrix::game_matrix::BuildViewMatrix(view_mat, word_mat);
	return view_mat;
}

void Camera::CenterCamera(float& x, float& y)
{
	x -= cameraCenterOnX;
	y -= cameraCenterOnY;
}