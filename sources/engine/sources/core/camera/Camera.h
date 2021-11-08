#pragma once
#include "math/Vector.h"
#include "math/Matrix.h"
#include "entities/GameObject.h"

class Camera
{
public:
	Camera(const vec_3x& position, const vec_3x& rotation);
	~Camera() {};

	void SetPosition(const vec_3x& position);	
	void SetRotation(const vec_3x& rotation);	
	
	void AttachCameraToObject(GameObject* obj);
	void DetachCameraFromObject();
	bool IsCameraAttachedToObject() { return attachedObject != nullptr; }

	const mat_4x& GetViewMatrix();

private:

	const mat_4x& BuildViewMatrixUsingAttachedObject();
	const mat_4x& BuildViewMatrixWithoutAttachedObject();
	const mat_4x& BuildViewMatrix(const float scale, const float posX, const float posY, const float posZ);

	void CenterCamera(float& x, float& y);

private:
	mat_4x word_mat;
	mat_4x view_mat;

	vec_3x camera_position;
	vec_3x camera_rotation;

	float cameraCenterOnX, cameraCenterOnY;

	GameObject* attachedObject = nullptr;

	const mat_4x& (Camera::*buildMatrixPtr)();
};