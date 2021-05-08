#include "Vector.h"
#include <stdio.h>
#include <math.h>



void vector::vector_2x::SetVector(vec_2x& R, const float vec_x, const float vec_y)
{
	R.elem[0] = vec_x;
	R.elem[1] = vec_y;
}

void vector::vector_2x::SetVector(vec_2x& R, const vec_2x& A)
{
	R.elem[0] = A.elem[0];
	R.elem[1] = A.elem[1];
}

void vector::vector_2x::Subtraction(vec_2x& R, const vec_2x& A, const vec_2x& B)
{
	R.elem[0] = A.elem[0] - B.elem[0];
	R.elem[1] = A.elem[1] - B.elem[1];
}

float vector::vector_2x::Magnitude(const vec_2x& A)
{
	return sqrt(double((A.elem[0] * A.elem[0]) +
					   (A.elem[1] * A.elem[1])));
}

void vector::vector_2x::Normalization(vec_2x& R, const vec_2x& vector)
{
	float mag = vector::vector_2x::Magnitude(vector);

	if (mag < 0.00001f)
		mag = 0.00001f;

	R.elem[0] = vector.elem[0] / mag;
	R.elem[1] = vector.elem[1] / mag;
}

void vector::vector_2x::Perpendicular(vec_2x& R, const vec_2x& vector)
{
	float swap = vector.elem[0];
	R.elem[0] = vector.elem[1];
	R.elem[1] = -swap;
}

void vector::vector_3x::SetVector(vec_3x& R, const float vec_x, const float vec_y, const float vec_z)
{
	R.elem[0] = vec_x;
	R.elem[1] = vec_y;
	R.elem[2] = vec_z;
}

void vector::vector_3x::SetVector(vec_3x& R, const vec_3x& A)
{
	R.elem[0] = A.elem[0];
	R.elem[1] = A.elem[1];
	R.elem[2] = A.elem[2];
}

void vector::vector_3x::Addition(vec_3x& R, const vec_3x& A, const vec_3x& B)
{
	R.elem[0] = A.elem[0] + B.elem[0];
	R.elem[1] = A.elem[1] + B.elem[1];
	R.elem[2] = A.elem[2] + B.elem[2];
}

void vector::vector_3x::Subtraction(vec_3x& R, const vec_3x& A, const vec_3x& B)
{
	R.elem[0] = A.elem[0] - B.elem[0];
	R.elem[1] = A.elem[1] - B.elem[1];
	R.elem[2] = A.elem[2] - B.elem[2];
}

void vector::vector_3x::DotProduct(vec_3x& R, const vec_3x& A, const float scalar)
{
	R.elem[0] = A.elem[0] * scalar;
	R.elem[1] = A.elem[1] * scalar;
	R.elem[2] = A.elem[2] * scalar;
}

float vector::vector_3x::DotProduct(const vec_3x& A, const vec_3x& B)
{
	return ((A.elem[0] * B.elem[0]) + 
		    (A.elem[1] * B.elem[1]) + 
			(A.elem[2] * B.elem[2]));
}

bool vector::vector_3x::IsEqual(const vec_3x& A, const vec_3x& B)
{
	bool result = true;

	for(int i = 0; i < 3; ++i)
	{
		if (A.elem[i] != B.elem[i])
		{
			result = false;
			break;
		}	
	}

	return result;
}

float vector::vector_3x::Magnitude(const vec_3x& A)
{
	return sqrt(double((A.elem[0] * A.elem[0]) + 
		               (A.elem[1] * A.elem[1]) + 
					   (A.elem[2] * A.elem[2])));
}

void vector::vector_3x::CrossProduct(vec_3x& R, const vec_3x& A, const vec_3x& B)
{
	R.elem[0] = (A.elem[1] * B.elem[2]) - (A.elem[2] * B.elem[1]);
	R.elem[1] = (A.elem[2] * B.elem[0]) - (A.elem[0] * B.elem[2]);
	R.elem[2] = (A.elem[0] * B.elem[1]) - (A.elem[1] * B.elem[0]);
}

void vector::vector_3x::Normalization(vec_3x& R, const vec_3x& vector)
{
	float mag = vector::vector_3x::Magnitude(vector);

	if(mag < 0.00001f)
	   mag = 0.00001f;

	R.elem[0] = vector.elem[0] / mag;
	R.elem[1] = vector.elem[1] / mag;
	R.elem[2] = vector.elem[2] / mag;
}

void vector::vector_4x::Normalization(vec_4x& R, const vec_4x& vector)
{
	float mag = vector::vector_4x::Magnitude(vector);

	if(mag < 0.00001f)
	   mag = 0.00001f;

	R.elem[0] = vector.elem[0] / mag;
	R.elem[1] = vector.elem[1] / mag;
	R.elem[2] = vector.elem[2] / mag;
	R.elem[3] = vector.elem[3] / mag;
}

float vector::vector_3x::AngleBetwVec(const vec_3x& A, const vec_3x& B)
{
	return acos(DotProduct(A, B) / (Magnitude(A) * Magnitude(B)));
}

float vector::vector_4x::AngleBetwVec(const vec_4x& A, const vec_4x& B)
{
	return acos(DotProduct(A, B) / (Magnitude(A) * Magnitude(B)));
}

void vector::vector_3x::VectorProjection(vec_3x& R, const vec_3x& proj, const vec_3x& onto)
{
	const float mag = Magnitude(proj);
	const float ang = cos(AngleBetwVec(proj, onto));
	const float new_vector_len = ang * mag;   // The magnitude of the prof. vector

	vec_3x onto_temp;
	Normalization(onto_temp, onto);

	// Computing the direction
	R.elem[0] = onto_temp.elem[0] * new_vector_len;
	R.elem[1] = onto_temp.elem[1] * new_vector_len;
	R.elem[2] = onto_temp.elem[2] * new_vector_len;
}

void vector::vector_4x::VectorProjection(vec_4x& R, const vec_4x& proj, const vec_4x& onto)
{
	const float mag = Magnitude(proj);
	const float ang = cos(AngleBetwVec(proj, onto));
	const float new_vector_len = ang * mag;    // The magnitude of the prof. vector

	vec_4x   onto_temp;
	Normalization(onto_temp, onto);

	// Computing the direction
	R.elem[0] = onto_temp.elem[0] * new_vector_len;
	R.elem[1] = onto_temp.elem[1] * new_vector_len;
	R.elem[2] = onto_temp.elem[2] * new_vector_len;
	R.elem[3] = onto_temp.elem[3] * new_vector_len;
}

void vector::vector_4x::SetVector(vec_4x& R, const float vec_x, const float vec_y, const float vec_z, const float vec_w)
{
	R.elem[0] = vec_x;
	R.elem[1] = vec_y;
	R.elem[2] = vec_z;
	R.elem[3] = vec_w;
}

void vector::vector_4x::SetVector(vec_4x& R, const vec_4x& A)
{
	R.elem[0] = A.elem[0];
	R.elem[1] = A.elem[1];
	R.elem[2] = A.elem[2];
	R.elem[3] = A.elem[3];
}

void vector::vector_4x::Addition(vec_4x& R, const vec_4x& A, const vec_4x& B)
{
	R.elem[0] = A.elem[0] + B.elem[0];
	R.elem[1] = A.elem[1] + B.elem[1];
	R.elem[2] = A.elem[2] + B.elem[2];
	R.elem[3] = A.elem[3] + B.elem[3];
}

void vector::vector_4x::Subtraction(vec_4x& R, const vec_4x& A, const vec_4x& B)
{
	R.elem[0] = A.elem[0] - B.elem[0];
	R.elem[1] = A.elem[1] - B.elem[1];
	R.elem[2] = A.elem[2] - B.elem[2];
	R.elem[3] = A.elem[3] - B.elem[3];
}

void vector::vector_4x::DotProduct(vec_4x& R, const vec_4x& A, const float scalar)
{
	R.elem[0] = A.elem[0] * scalar;
	R.elem[1] = A.elem[1] * scalar;
	R.elem[2] = A.elem[2] * scalar;
	R.elem[3] = A.elem[3] * scalar;
}

float vector::vector_4x::DotProduct(const vec_4x& A, const vec_4x& B)
{
	return ((A.elem[0] * B.elem[0]) + 
		    (A.elem[1] * B.elem[1]) + 
			(A.elem[2] * B.elem[2]) + 
			(A.elem[3] * B.elem[3]));
}

bool vector::vector_4x::IsEqual(const vec_4x& A, const vec_4x& B)
{
	bool result = true;

	for (int i = 0; i < 4; ++i)
	{
		if (A.elem[i] != B.elem[i])
		{
			result = false;
			break;
		}
	}

	return result;
}

float vector::vector_4x::Magnitude(const vec_4x& A)
{
	return sqrt(double((A.elem[0] * A.elem[0]) + 
		               (A.elem[1] * A.elem[1]) + 
					   (A.elem[2] * A.elem[2]) +
					   (A.elem[3] * A.elem[3])));
}

void vector::vector_game::ScreenToWorld(const vec_3x screen_pos, vec_3x& world_pos,
										const float world_width_right, const float world_height_down,
										const float screen_w, const float screen_h)
{

}

//TODO can I delete them, because i don't use them?
void vector::vector_game::WorldToScreen(const vec_3x world_pos, vec_3x& screen_pos, 
	                                    const float world_width_right, const float world_height_down,
										const float screen_w, const float screen_h)
{
	/* Convert object pos (relative) to screen resolution */
	/* src - source coordinate system */
	/* res - result coordination system */
	/* res = ( src - src_min ) / ( src_max - src_min ) * ( res_max - res_min ) + res_min */
	screen_pos.elem[0] = world_pos.elem[0] / world_width_right * screen_w;
	screen_pos.elem[1] = world_pos.elem[1] / world_height_down * screen_h;
}

//TODO can I delete them, because i don't use them?
void vector::vector_game::WorldToScreen(const float world_pos_x, const float world_pos_y,
										float& screen_pos_x, float& screen_pos_y,
										const float world_width_right, const float world_height_down,
										const float screen_w, const float screen_h)
{
	/* Convert object pos (relative) to screen resolution */
	/* src - source coordinate system */
	/* res - result coordination system */
	/* res = ( src - src_min ) / ( src_max - src_min ) * ( res_max - res_min ) + res_min */
	screen_pos_x = world_pos_x / world_width_right * screen_w;
	screen_pos_y = world_pos_y / world_height_down * screen_h;
}




/*
Vector* Vector::operator + (Vector* A)
{
	Vector* temp = new Vector;

	temp->SetVector4x(this->ReturnVec4x());

	temp->Addition4x(*A);	

	return temp;	
}

Vector* Vector::operator - (Vector* A)
{
	Vector* temp = new Vector;

	temp->SetVector4x(this->ReturnVec4x());

	temp->Subtraction4x(*A);	

	return temp;	
}

Vector* Vector::operator * (float A)
{
	Vector* temp = new Vector;

	temp->SetVector4x(this->ReturnVec4x());

	temp->DotProduct4x(A);	

	return temp;	
}

Vector* Vector::operator * (Vector* A)
{
	Vector* temp = new Vector;

	temp->SetVector4x(this->ReturnVec4x());

	temp->DotProduct4x(*A);	

	return temp;	
}*/