#include "Matrix.h"
#include <string>

#if(LINUX_PLATFORM)
#include <string.h> // Added for memcpy
#include <math.h>	// Added for math functions
#endif


void matrix::matrix_4x::SetMatrix(mat_4x& R, const mat_4x& A)
{
	memcpy(&R, &A, sizeof(mat_4x)); 
}

void matrix::matrix_4x::SetMatrix(mat_4x& R, const float m01, const float m02, const float m03, const float m04,
											 const float m05, const float m06, const float m07, const float m08,
											 const float m09, const float m10, const float m11, const float m12,
											 const float m13, const float m14, const float m15, const float m16)
{

	R.elem[0][0] = m01;
	R.elem[0][1] = m02;
	R.elem[0][2] = m03;
	R.elem[0][3] = m04;

	R.elem[1][0] = m05;
	R.elem[1][1] = m06;
	R.elem[1][2] = m07;
	R.elem[1][3] = m08;

	R.elem[2][0] = m09;
	R.elem[2][1] = m10;
	R.elem[2][2] = m11;
	R.elem[2][3] = m12;

	R.elem[3][0] = m13;
	R.elem[3][1] = m14;
	R.elem[3][2] = m15;
	R.elem[3][3] = m16;
}

void matrix::matrix_4x::SetIdentity(mat_4x& R)
{

	R.elem[0][0] = 1.0f;
	R.elem[0][1] = 0.0f;
	R.elem[0][2] = 0.0f;
	R.elem[0][3] = 0.0f;

	R.elem[1][0] = 0.0f;
	R.elem[1][1] = 1.0f;
	R.elem[1][2] = 0.0f;
	R.elem[1][3] = 0.0f;

	R.elem[2][0] = 0.0f;
	R.elem[2][1] = 0.0f;
	R.elem[2][2] = 1.0f;
	R.elem[2][3] = 0.0f;

	R.elem[3][0] = 0.0f;
	R.elem[3][1] = 0.0f;
	R.elem[3][2] = 0.0f;
	R.elem[3][3] = 1.0f;
}

void matrix::matrix_4x::Addition(mat_4x& R, const mat_4x& A, const mat_4x& B)
{
	R.elem[0][0] = A.elem[0][0] + A.elem[0][0];
	R.elem[0][1] = A.elem[0][1] + A.elem[0][1];
	R.elem[0][2] = A.elem[0][2] + A.elem[0][2];
	R.elem[0][3] = A.elem[0][3] + A.elem[0][3];

	R.elem[1][0] = A.elem[1][0] + A.elem[1][0];
	R.elem[1][1] = A.elem[1][1] + A.elem[1][1];
	R.elem[1][2] = A.elem[1][2] + A.elem[1][2];
	R.elem[1][3] = A.elem[1][3] + A.elem[1][3];

	R.elem[2][0] = A.elem[2][0] + A.elem[2][0];
	R.elem[2][1] = A.elem[2][1] + A.elem[2][1];
	R.elem[2][2] = A.elem[2][2] + A.elem[2][2];
	R.elem[2][3] = A.elem[2][3] + A.elem[2][3];

	R.elem[3][0] = A.elem[3][0] + A.elem[3][0];
	R.elem[3][1] = A.elem[3][1] + A.elem[3][1];
	R.elem[3][2] = A.elem[3][2] + A.elem[3][2];
	R.elem[3][3] = A.elem[3][3] + A.elem[3][3];
}

void matrix::matrix_4x::Subtraction(mat_4x& R, const mat_4x& A, const mat_4x& B)
{
	R.elem[0][0] = A.elem[0][0] - A.elem[0][0];
	R.elem[0][1] = A.elem[0][1] - A.elem[0][1];
	R.elem[0][2] = A.elem[0][2] - A.elem[0][2];
	R.elem[0][3] = A.elem[0][3] - A.elem[0][3];

	R.elem[1][0] = A.elem[1][0] - A.elem[1][0];
	R.elem[1][1] = A.elem[1][1] - A.elem[1][1];
	R.elem[1][2] = A.elem[1][2] - A.elem[1][2];
	R.elem[1][3] = A.elem[1][3] - A.elem[1][3];

	R.elem[2][0] = A.elem[2][0] - A.elem[2][0];
	R.elem[2][1] = A.elem[2][1] - A.elem[2][1];
	R.elem[2][2] = A.elem[2][2] - A.elem[2][2];
	R.elem[2][3] = A.elem[2][3] - A.elem[2][3];

	R.elem[3][0] = A.elem[3][0] - A.elem[3][0];
	R.elem[3][1] = A.elem[3][1] - A.elem[3][1];
	R.elem[3][2] = A.elem[3][2] - A.elem[3][2];
	R.elem[3][3] = A.elem[3][3] - A.elem[3][3];
}

void matrix::matrix_4x::Multiply(mat_4x& R, const mat_4x& A, const float scalar)
{
	for(int i = 0; i < MAX_COL_4X; i++)
		for(int j = 0; j < MAX_ROW_4X; j++)
			R.elem[i][j] = A.elem[i][j] * scalar;
}

//TODO: implement a better multiplication algo (see wikipedia)
//there are many optimized libs which work with math operations
//http://www.netlib.org/utk/papers/autoblock/node2.html
//http://www.netlib.org/lapack/
void matrix::matrix_4x::Multiply(mat_4x& R, const mat_4x& A, const mat_4x& B)
{
	// matrix * matrix
	R.elem[0][0] = (A.elem[0][0] * B.elem[0][0]) + (A.elem[0][1] * B.elem[1][0]) + (A.elem[0][2] * B.elem[2][0]) + (A.elem[0][3] * B.elem[3][0]);
	R.elem[0][1] = (A.elem[0][0] * B.elem[0][1]) + (A.elem[0][1] * B.elem[1][1]) + (A.elem[0][2] * B.elem[2][1]) + (A.elem[0][3] * B.elem[3][1]);
	R.elem[0][2] = (A.elem[0][0] * B.elem[0][2]) + (A.elem[0][1] * B.elem[1][2]) + (A.elem[0][2] * B.elem[2][2]) + (A.elem[0][3] * B.elem[3][2]);
	R.elem[0][3] = (A.elem[0][0] * B.elem[0][3]) + (A.elem[0][1] * B.elem[1][3]) + (A.elem[0][2] * B.elem[2][3]) + (A.elem[0][3] * B.elem[3][3]);

	R.elem[1][0] = (A.elem[1][0] * B.elem[0][0]) + (A.elem[1][1] * B.elem[1][0]) + (A.elem[1][2] * B.elem[2][0]) + (A.elem[1][3] * B.elem[3][0]);
	R.elem[1][1] = (A.elem[1][0] * B.elem[0][1]) + (A.elem[1][1] * B.elem[1][1]) + (A.elem[1][2] * B.elem[2][1]) + (A.elem[1][3] * B.elem[3][1]);
	R.elem[1][2] = (A.elem[1][0] * B.elem[0][2]) + (A.elem[1][1] * B.elem[1][2]) + (A.elem[1][2] * B.elem[2][2]) + (A.elem[1][3] * B.elem[3][2]);
	R.elem[1][3] = (A.elem[1][0] * B.elem[0][3]) + (A.elem[1][1] * B.elem[1][3]) + (A.elem[1][2] * B.elem[2][3]) + (A.elem[1][3] * B.elem[3][3]);

	R.elem[2][0] = (A.elem[2][0] * B.elem[0][0]) + (A.elem[2][1] * B.elem[1][0]) + (A.elem[2][2] * B.elem[2][0]) + (A.elem[2][3] * B.elem[3][0]);
	R.elem[2][1] = (A.elem[2][0] * B.elem[0][1]) + (A.elem[2][1] * B.elem[1][1]) + (A.elem[2][2] * B.elem[2][1]) + (A.elem[2][3] * B.elem[3][1]);
	R.elem[2][2] = (A.elem[2][0] * B.elem[0][2]) + (A.elem[2][1] * B.elem[1][2]) + (A.elem[2][2] * B.elem[2][2]) + (A.elem[2][3] * B.elem[3][2]);
	R.elem[2][3] = (A.elem[2][0] * B.elem[0][3]) + (A.elem[2][1] * B.elem[1][3]) + (A.elem[2][2] * B.elem[2][3]) + (A.elem[2][3] * B.elem[3][3]);

	R.elem[3][0] = (A.elem[3][0] * B.elem[0][0]) + (A.elem[3][1] * B.elem[1][0]) + (A.elem[3][2] * B.elem[2][0]) + (A.elem[3][3] * B.elem[3][0]);
	R.elem[3][1] = (A.elem[3][0] * B.elem[0][1]) + (A.elem[3][1] * B.elem[1][1]) + (A.elem[3][2] * B.elem[2][1]) + (A.elem[3][3] * B.elem[3][1]);
	R.elem[3][2] = (A.elem[3][0] * B.elem[0][2]) + (A.elem[3][1] * B.elem[1][2]) + (A.elem[3][2] * B.elem[2][2]) + (A.elem[3][3] * B.elem[3][2]);
	R.elem[3][3] = (A.elem[3][0] * B.elem[0][3]) + (A.elem[3][1] * B.elem[1][3]) + (A.elem[3][2] * B.elem[2][3]) + (A.elem[3][3] * B.elem[3][3]);
}

void matrix::matrix_4x::Multiply(vec_4x& R, const vec_4x& vec, const mat_4x& mat)
{
	// vector * matrix
	R.elem[0] = (vec.elem[0] * mat.elem[0][0]) + (vec.elem[1] * mat.elem[1][0]) + (vec.elem[2] * mat.elem[2][0]) + (vec.elem[3] * mat.elem[3][0]);
	R.elem[1] = (vec.elem[0] * mat.elem[0][1]) + (vec.elem[1] * mat.elem[1][1]) + (vec.elem[2] * mat.elem[2][1]) + (vec.elem[3] * mat.elem[3][1]);
	R.elem[2] = (vec.elem[0] * mat.elem[0][2]) + (vec.elem[1] * mat.elem[1][2]) + (vec.elem[2] * mat.elem[2][2]) + (vec.elem[3] * mat.elem[3][2]);
	R.elem[3] = (vec.elem[0] * mat.elem[0][3]) + (vec.elem[1] * mat.elem[1][3]) + (vec.elem[2] * mat.elem[2][3]) + (vec.elem[3] * mat.elem[3][3]);
}

float matrix::matrix_4x::Minor(const float m01, const float m02, const float m03,
							   const float m04, const float m05, const float m06,
							   const float m07, const float m08, const float m09)
{
	return (m01 * m05 * m09) + (m04 * m08 * m03) + (m07 * m02 * m06) -
		   (m03 * m05 * m07) - (m06 * m08 * m01) - (m09 * m02 * m04);
}

float matrix::matrix_4x::Determinant(const mat_4x& mat)
{

	return	mat.elem[0][0] * matrix::matrix_4x::Minor(mat.elem[1][1], mat.elem[1][2], mat.elem[1][3],
													  mat.elem[2][1], mat.elem[2][2], mat.elem[2][3],
												      mat.elem[3][1], mat.elem[3][2], mat.elem[3][3]) -
			mat.elem[0][1] * matrix::matrix_4x::Minor(mat.elem[1][0], mat.elem[1][2], mat.elem[1][3],
													  mat.elem[2][0], mat.elem[2][2], mat.elem[2][3],
													  mat.elem[3][0], mat.elem[3][2], mat.elem[3][3]) +
			mat.elem[0][2] * matrix::matrix_4x::Minor(mat.elem[1][0], mat.elem[1][1], mat.elem[1][3],
													  mat.elem[2][0], mat.elem[2][1], mat.elem[2][3],
													  mat.elem[3][0], mat.elem[3][1], mat.elem[3][3]) -
			mat.elem[0][3] * matrix::matrix_4x::Minor(mat.elem[1][0], mat.elem[1][1], mat.elem[1][2],
													  mat.elem[2][0], mat.elem[2][1], mat.elem[2][2],
													  mat.elem[3][0], mat.elem[3][1], mat.elem[3][2]);
}

void matrix::matrix_4x::Transpoze(mat_4x& R, const mat_4x& to_trans)
{
	R.elem[0][0] = to_trans.elem[0][0];
	R.elem[0][1] = to_trans.elem[1][0];
	R.elem[0][2] = to_trans.elem[2][0];
	R.elem[0][3] = to_trans.elem[3][0];

	R.elem[1][0] = to_trans.elem[0][1];
	R.elem[1][1] = to_trans.elem[1][1];
	R.elem[1][2] = to_trans.elem[2][1];
	R.elem[1][3] = to_trans.elem[3][1];

	R.elem[2][0] = to_trans.elem[0][2];
	R.elem[2][1] = to_trans.elem[1][2];
	R.elem[2][2] = to_trans.elem[2][2];
	R.elem[2][3] = to_trans.elem[3][2];

	R.elem[3][0] = to_trans.elem[0][3];
	R.elem[3][1] = to_trans.elem[1][3];
	R.elem[3][2] = to_trans.elem[2][3];
	R.elem[3][3] = to_trans.elem[3][3];
}

void matrix::matrix_4x::Inverse(mat_4x& R, const mat_4x& to_inv)
{
	const float det = matrix::matrix_4x::Determinant(to_inv);

	if(det == 0.0f)
	{
		printf("The matrix is singular, is not invertable !\n");
		return;
	}

	Adjugate(R, to_inv);
	Multiply(R, to_inv, (1.0f / det));
}

void matrix::matrix_4x::Adjugate(mat_4x& R, const mat_4x& A)
{
	// The calculation of the 3x3 minors
	R.elem[0][0] = Minor(A.elem[1][1], A.elem[1][2], A.elem[1][3], A.elem[2][1], A.elem[2][2], A.elem[2][3], A.elem[3][1], A.elem[3][2], A.elem[3][3]);
	R.elem[0][1] = -Minor(A.elem[1][0], A.elem[1][2], A.elem[1][3], A.elem[2][0], A.elem[2][2], A.elem[2][3], A.elem[3][0], A.elem[3][2], A.elem[3][3]);
	R.elem[0][2] = Minor(A.elem[1][0], A.elem[1][1], A.elem[1][3], A.elem[2][0], A.elem[2][1], A.elem[2][3], A.elem[3][0], A.elem[3][1], A.elem[3][3]);
	R.elem[0][3] = -Minor(A.elem[1][0], A.elem[1][1], A.elem[1][2], A.elem[2][0], A.elem[2][1], A.elem[2][2], A.elem[3][0], A.elem[3][1], A.elem[3][2]);

	R.elem[1][0] = -Minor(A.elem[0][1], A.elem[0][2], A.elem[0][3], A.elem[2][1], A.elem[2][2], A.elem[2][3], A.elem[3][1], A.elem[3][2], A.elem[3][3]);
	R.elem[1][1] = Minor(A.elem[0][0], A.elem[0][2], A.elem[0][3], A.elem[2][0], A.elem[2][2], A.elem[2][3], A.elem[3][0], A.elem[3][2], A.elem[3][3]);
	R.elem[1][2] = -Minor(A.elem[0][0], A.elem[0][1], A.elem[0][3], A.elem[2][0], A.elem[2][1], A.elem[2][3], A.elem[3][0], A.elem[3][1], A.elem[3][3]);
	R.elem[1][3] = Minor(A.elem[0][0], A.elem[0][1], A.elem[0][2], A.elem[2][0], A.elem[2][1], A.elem[2][2], A.elem[3][0], A.elem[3][1], A.elem[3][2]);

	R.elem[2][0] = Minor(A.elem[0][1], A.elem[0][2], A.elem[0][3], A.elem[1][1], A.elem[1][2], A.elem[1][3], A.elem[3][1], A.elem[3][2], A.elem[3][3]);
	R.elem[2][1] = -Minor(A.elem[0][0], A.elem[0][2], A.elem[0][3], A.elem[1][0], A.elem[1][2], A.elem[1][3], A.elem[3][0], A.elem[3][2], A.elem[3][3]);
	R.elem[2][2] = Minor(A.elem[0][0], A.elem[0][1], A.elem[0][3], A.elem[1][0], A.elem[1][1], A.elem[1][3], A.elem[3][0], A.elem[3][1], A.elem[3][3]);
	R.elem[2][3] = -Minor(A.elem[0][0], A.elem[0][1], A.elem[0][2], A.elem[1][0], A.elem[1][1], A.elem[1][2], A.elem[3][0], A.elem[3][1], A.elem[3][2]);

	R.elem[3][0] = -Minor(A.elem[0][1], A.elem[0][2], A.elem[0][3], A.elem[1][1], A.elem[1][2], A.elem[1][3], A.elem[2][1], A.elem[2][2], A.elem[2][3]);
	R.elem[3][1] = Minor(A.elem[0][0], A.elem[0][2], A.elem[0][3], A.elem[1][0], A.elem[1][2], A.elem[1][3], A.elem[2][0], A.elem[2][2], A.elem[2][3]);
	R.elem[3][2] = -Minor(A.elem[0][0], A.elem[0][1], A.elem[0][3], A.elem[1][0], A.elem[1][1], A.elem[1][3], A.elem[2][0], A.elem[2][1], A.elem[2][3]);
	R.elem[3][3] = Minor(A.elem[0][0], A.elem[0][1], A.elem[0][2], A.elem[1][0], A.elem[1][1], A.elem[1][2], A.elem[2][0], A.elem[2][1], A.elem[2][2]);
}

void matrix::matrix_4x::PrintIt(mat_4x& R)
{	
	printf("_______________________________\n");
	printf(" %f, %f, %f, %f\n", R.elem[0][0], R.elem[0][1], R.elem[0][2], R.elem[0][3]);
	printf(" %f, %f, %f, %f\n", R.elem[1][0], R.elem[1][1], R.elem[1][2], R.elem[1][3]);
	printf(" %f, %f, %f, %f\n", R.elem[2][0], R.elem[2][1], R.elem[2][2], R.elem[2][3]);
	printf(" %f, %f, %f, %f\n", R.elem[3][0], R.elem[3][1], R.elem[3][2], R.elem[3][3]);
	printf("_______________________________");
}

void matrix::matrix_3x::SetIdentity(mat_3x& R)
{
	R.elem[0][0] = 1.0f;
	R.elem[0][1] = 0.0f;
	R.elem[0][2] = 0.0f;

	R.elem[1][0] = 0.0f;
	R.elem[1][1] = 1.0f;
	R.elem[1][2] = 0.0f;

	R.elem[2][0] = 0.0f;
	R.elem[2][1] = 0.0f;
	R.elem[2][2] = 1.0f;
}

void matrix::matrix_3x::SetMatrix(mat_3x& R, const float m01, const float m02, const float m03, 
											 const float m04, const float m05, const float m06,
											 const float m07, const float m08, const float m09)
{
	R.elem[0][0] = m01;
	R.elem[0][1] = m02;
	R.elem[0][2] = m03;

	R.elem[1][0] = m04;
	R.elem[1][1] = m05;
	R.elem[1][2] = m06;

	R.elem[2][0] = m07;
	R.elem[2][1] = m08;
	R.elem[2][2] = m09;
}

void matrix::matrix_3x::SetMatrix(mat_3x& R, const mat_3x& A)
{
    memcpy(&R, &A, sizeof(mat_3x)); 
}

void matrix::matrix_3x::Addition(mat_3x& R, const mat_3x& A)
{
	R.elem[0][0] += A.elem[0][0];
	R.elem[0][1] += A.elem[0][1];
	R.elem[0][2] += A.elem[0][2];

	R.elem[1][0] += A.elem[1][0];
	R.elem[1][1] += A.elem[1][1];
	R.elem[1][2] += A.elem[1][2];

	R.elem[2][0] += A.elem[2][0];
	R.elem[2][1] += A.elem[2][1];
	R.elem[2][2] += A.elem[2][2];
}

void matrix::matrix_3x::Subtraction(mat_3x& R, const mat_3x& A)
{
	R.elem[0][0] -= A.elem[0][0];
	R.elem[0][1] -= A.elem[0][1];
	R.elem[0][2] -= A.elem[0][2];

	R.elem[1][0] -= A.elem[1][0];
	R.elem[1][1] -= A.elem[1][1];
	R.elem[1][2] -= A.elem[1][2];

	R.elem[2][0] -= A.elem[2][0];
	R.elem[2][1] -= A.elem[2][1];
	R.elem[2][2] -= A.elem[2][2];
}

void matrix::matrix_3x::Multiply(mat_3x& R, const mat_3x& A, const float scalar)
{
	for(int i = 0; i < MAX_COL_3X; i++)
		for(int j = 0; j < MAX_ROW_3X; j++)
			R.elem[i][j] = A.elem[i][j] * scalar;
}

void matrix::matrix_3x::Multiply(mat_3x& R, const mat_3x& A, const mat_3x& B)
{
	R.elem[0][0] = (A.elem[0][0] * B.elem[0][0]) + (A.elem[0][1] * B.elem[1][0]) + (A.elem[0][2] * B.elem[2][0]);
	R.elem[0][1] = (A.elem[0][0] * B.elem[0][1]) + (A.elem[0][1] * B.elem[1][1]) + (A.elem[0][2] * B.elem[2][1]);
	R.elem[0][2] = (A.elem[0][0] * B.elem[0][2]) + (A.elem[0][1] * B.elem[1][2]) + (A.elem[0][2] * B.elem[2][2]);

	R.elem[1][0] = (A.elem[1][0] * B.elem[0][0]) + (A.elem[1][1] * B.elem[1][0]) + (A.elem[1][2] * B.elem[2][0]);
	R.elem[1][1] = (A.elem[1][0] * B.elem[0][1]) + (A.elem[1][1] * B.elem[1][1]) + (A.elem[1][2] * B.elem[2][1]);
	R.elem[1][2] = (A.elem[1][0] * B.elem[0][2]) + (A.elem[1][1] * B.elem[1][2]) + (A.elem[1][2] * B.elem[2][2]);

	R.elem[2][0] = (A.elem[2][0] * B.elem[0][0]) + (A.elem[2][1] * B.elem[1][0]) + (A.elem[2][2] * B.elem[2][0]);
	R.elem[2][1] = (A.elem[2][0] * B.elem[0][1]) + (A.elem[2][1] * B.elem[1][1]) + (A.elem[2][2] * B.elem[2][1]);
	R.elem[2][2] = (A.elem[2][0] * B.elem[0][2]) + (A.elem[2][1] * B.elem[1][2]) + (A.elem[2][2] * B.elem[2][2]);
}

void matrix::matrix_3x::Multiply(vec_3x& R, const vec_3x& vec, const mat_3x& mat)
{
	// Vector * Matrixe
	R.elem[0] = (vec.elem[0] * mat.elem[0][0]) + (vec.elem[1] * mat.elem[1][0]) + (vec.elem[2] * mat.elem[2][0]);
	R.elem[1] = (vec.elem[0] * mat.elem[0][1]) + (vec.elem[1] * mat.elem[1][1]) + (vec.elem[2] * mat.elem[2][1]);
	R.elem[2] = (vec.elem[0] * mat.elem[0][2]) + (vec.elem[1] * mat.elem[1][2]) + (vec.elem[2] * mat.elem[2][2]);
}

float matrix::matrix_3x::Determinant(const mat_3x& mat)
{
	return (mat.elem[0][0] * mat.elem[1][1] * mat.elem[2][2]) +
		   (mat.elem[0][2] * mat.elem[1][0] * mat.elem[2][1]) +
		   (mat.elem[0][1] * mat.elem[1][2] * mat.elem[2][0]) -
		   (mat.elem[0][2] * mat.elem[1][1] * mat.elem[2][0]) -
		   (mat.elem[0][1] * mat.elem[1][0] * mat.elem[2][2]) -
		   (mat.elem[0][0] * mat.elem[1][0] * mat.elem[2][1]);
}

void matrix::matrix_3x::Transpoze(mat_3x& R)
{
	mat_3x  tempM;
	SetMatrix(tempM, R);

	R.elem[0][0] = tempM.elem[0][0];
	R.elem[0][1] = tempM.elem[1][0];
	R.elem[0][2] = tempM.elem[2][0];

	R.elem[1][0] = tempM.elem[0][1];
	R.elem[1][1] = tempM.elem[1][1];
	R.elem[1][2] = tempM.elem[2][1];

	R.elem[2][0] = tempM.elem[0][2];
	R.elem[2][1] = tempM.elem[1][2];
	R.elem[2][2] = tempM.elem[2][2];
}

float matrix::matrix_3x::Minor(const float m01, const float m02, const float m03, const float m04)
{
	return (m01 * m04) - (m02 * m03);
}

void matrix::matrix_3x::Inverse(mat_3x& R)
{
	float det = matrix::matrix_3x::Determinant(R);

	if(det == 0.0f)
	{
		printf("The matrix is singular, is not invertable !\n");
		return;
	}

	Adjugate(R);
	Multiply(R, R, (1.0f / det));
}

void matrix::matrix_3x::Adjugate(mat_3x& R)
{
	mat_3x tempM; 

	matrix::matrix_3x::SetMatrix(tempM, R);


	matrix::matrix_3x::Transpoze(R);
	matrix::matrix_3x::Transpoze(tempM);



	// The calculation of the 3x3 minors
	R.elem[0][0] =  Minor(tempM.elem[1][1], tempM.elem[1][2], tempM.elem[2][1], tempM.elem[2][2]);
	R.elem[0][1] = -Minor(tempM.elem[1][0], tempM.elem[1][2], tempM.elem[2][0], tempM.elem[2][2]);
	R.elem[0][2] =  Minor(tempM.elem[1][0], tempM.elem[1][1], tempM.elem[2][0], tempM.elem[2][1]);

	R.elem[1][0] = -Minor(tempM.elem[0][1], tempM.elem[0][2], tempM.elem[2][1], tempM.elem[2][2]);
	R.elem[1][1] =  Minor(tempM.elem[0][0], tempM.elem[0][2], tempM.elem[2][0], tempM.elem[2][2]);
	R.elem[1][2] = -Minor(tempM.elem[0][0], tempM.elem[0][1], tempM.elem[2][0], tempM.elem[2][1]);

	R.elem[2][0] =  Minor(tempM.elem[0][1], tempM.elem[0][2], tempM.elem[1][1], tempM.elem[1][2]);
	R.elem[2][1] = -Minor(tempM.elem[0][0], tempM.elem[0][2], tempM.elem[1][0], tempM.elem[1][2]);
	R.elem[2][2] =  Minor(tempM.elem[0][0], tempM.elem[0][1], tempM.elem[1][0], tempM.elem[1][1]);
}

void matrix::matrix_3x::PrintIt(const mat_3x& R)
{
	printf("_________________________\n");
	printf(" %f, %f, %f\n", R.elem[0][0], R.elem[0][1], R.elem[0][2]);
	printf(" %f, %f, %f\n", R.elem[1][0], R.elem[1][1], R.elem[1][2]);
	printf(" %f, %f, %f\n", R.elem[2][0], R.elem[2][1], R.elem[2][2]);
	printf("_________________________\n");
}


/*
Matrix4X Matrix4X::operator - (Matrix4X & A)
{
Matrix4X temp(*this);

temp.Subtraction(A);

return temp;
}


Matrix4X Matrix4X::operator * (float A)
{
Matrix4X temp(*this);

temp.Multiply(A);

return temp;
}


Matrix4X Matrix4X::operator * (Matrix4X & A)
{
Matrix4X temp(*this);

temp.Multiply(A);

return temp;
}*/

void matrix::game_matrix::SetWorldScale(mat_4x& R, const float scale)
{
	R.elem[0][0] *= scale;
	R.elem[1][1] *= scale;
	R.elem[2][2] *= scale;
}

void matrix::game_matrix::SetWorldPosition(mat_4x& R, const vec_3x& pos)
{
	R.elem[3][0] = pos.elem[0];
	R.elem[3][1] = pos.elem[1];
	R.elem[3][2] = pos.elem[2];
	R.elem[3][3] = 1.0f;			
}

void matrix::game_matrix::SetWorldPosition(mat_4x& R, const float pos_x, const float pos_y, const float pos_z)
{
	R.elem[3][0] = pos_x;
	R.elem[3][1] = pos_y;
	R.elem[3][2] = pos_z;
	R.elem[3][3] = 1.0f;			
}

void matrix::game_matrix::SetWorldRotation(mat_4x& R, const float pos_x, const float pos_y, const float pos_z)
{
	float cos_radX = cosf(pos_x);
	float sin_radX = sinf(pos_x);
	float cos_radY = cosf(pos_y);
	float sin_radY = sinf(pos_y);
	float cos_radZ = cosf(pos_z);
	float sin_radZ = sinf(pos_z);

	R.elem[0][0] = cos_radY * cos_radZ;
	R.elem[0][1] = cos_radY * sin_radZ;
	R.elem[0][2] = -sin_radY;
	R.elem[0][3] = 0.0f;

	R.elem[1][0] = (sin_radX * sin_radY * cos_radZ) + (cos_radX * (-sin_radZ));
	R.elem[1][1] = (sin_radX * sin_radY * sin_radZ) + (cos_radX * cos_radZ);
	R.elem[1][2] = sin_radX * cos_radY;
	R.elem[1][3] = 0.0f;

	R.elem[2][0] = (cos_radX * sin_radY * cos_radZ) + ((-sin_radX)*(-sin_radZ));
	R.elem[2][1] = (cos_radX * sin_radY * sin_radZ) + ((-sin_radX) * cos_radZ);
	R.elem[2][2] = cos_radX * cos_radY;
	R.elem[2][3] = 0.0f;

	R.elem[3][0] = 0.0f;
	R.elem[3][1] = 0.0f;
	R.elem[3][2] = 0.0f;
	R.elem[3][3] = 1.0f;
}

void matrix::game_matrix::SetWorldRotation(mat_4x& R, const vec_3x& rot)
{
	float cos_radX = cosf(rot.elem[0]);
	float sin_radX = sinf(rot.elem[0]);
	float cos_radY = cosf(rot.elem[1]);
	float sin_radY = sinf(rot.elem[1]);
	float cos_radZ = cosf(rot.elem[2]);
	float sin_radZ = sinf(rot.elem[2]);

	R.elem[0][0] = cos_radY * cos_radZ;
	R.elem[0][1] = cos_radY * sin_radZ;
	R.elem[0][2] = -sin_radY;
	R.elem[0][3] = 0.0f;

	R.elem[1][0] = (sin_radX * sin_radY * cos_radZ) + (cos_radX * (-sin_radZ));
	R.elem[1][1] = (sin_radX * sin_radY * sin_radZ) + (cos_radX * cos_radZ);
	R.elem[1][2] = sin_radX * cos_radY;
	R.elem[1][3] = 0.0f;

	R.elem[2][0] = (cos_radX * sin_radY * cos_radZ) + ((-sin_radX)*(-sin_radZ));
	R.elem[2][1] = (cos_radX * sin_radY * sin_radZ) + ((-sin_radX) * cos_radZ);
	R.elem[2][2] = cos_radX * cos_radY;
	R.elem[2][3] = 0.0f;

	R.elem[3][0] = 0.0f;
	R.elem[3][1] = 0.0f;
	R.elem[3][2] = 0.0f;
	R.elem[3][3] = 1.0f;
}

void BuildWorldMatrix(mat_4x& R, const vec_3x rotation, const vec_3x position, const float scale)
{
	matrix::game_matrix::BuildWorldMatrix(R, rotation.elem[0], rotation.elem[1], rotation.elem[2],
											 position.elem[0], position.elem[1], position.elem[2],
											 scale);
}

void matrix::game_matrix::BuildWorldMatrix(mat_4x& R, const float rotX, const float rotY, const float rotZ,
													  const float pozX, const float pozY, const float pozZ,
													  const float scale)
{
	matrix::game_matrix::SetWorldScale(R, scale);
	matrix::game_matrix::SetWorldPosition(R, pozX, pozY, pozZ);
	matrix::game_matrix::SetWorldRotation(R, rotX, rotY, rotZ);
}

void matrix::game_matrix::SetWorldPosAndRot(mat_4x& R, const vec_3x& pos, const vec_3x& rot)
{
	matrix::game_matrix::SetWorldRotation(R, rot.elem[0], rot.elem[1], rot.elem[2]);
	matrix::game_matrix::SetWorldPosition(R, pos.elem[0], pos.elem[1], pos.elem[2]);
}

void matrix::game_matrix::SetWorldPosAndRot(mat_4x& R, const float rotX, const float rotY, const float rotZ,
												       const float pozX, const float pozY, const float pozZ)
{
	matrix::game_matrix::SetWorldRotation(R, rotX, rotY, rotZ);
	matrix::game_matrix::SetWorldPosition(R, pozX, pozY, pozZ);
}

void matrix::game_matrix::BuildProjectionMatrix(mat_4x& R, const float left, const float right, const float bottom,
													  const float top, const float near, const float far)
{
	float result_a = right - left;
	float result_b = top - bottom;
	float result_c = far - near;

	matrix::matrix_4x::SetMatrix(R, (2.0f / result_a), 0.0f, 0.0f, 0.0f,
									0.0f, (2.0f / result_b), 0.0f, 0.0f,
									0.0f, 0.0f, (-2.0f / result_c), 0.0f,
									(-right / result_a), (-top / result_b), (-(far + near) / result_c), 1.0f);
}

void matrix::game_matrix::BuildWorldProjMatrix(mat_4x& R, const mat_4x& world, const mat_4x& proj)
{
	matrix::matrix_4x::Multiply(R, R, world);
	matrix::matrix_4x::Multiply(R, R, proj);
}

void matrix::game_matrix::BuildWorldViewProjMatrix(mat_4x& R, const mat_4x& world, const mat_4x& view, const mat_4x& proj)
{
	matrix::matrix_4x::Multiply(R, R, world);
	matrix::matrix_4x::Multiply(R, R, view);
	matrix::matrix_4x::Multiply(R, R, proj);
}

void matrix::game_matrix::BuildViewMatrix(mat_4x& R, const mat_4x& camera)
{
	vec_3x    CPos, CRight, CUp, CLook;
	float     valX, valY, valZ;

	CRight.elem[0] = camera.elem[0][0];
	CRight.elem[1] = camera.elem[0][1];
	CRight.elem[2] = camera.elem[0][2];

	CUp.elem[0] = camera.elem[1][0];
	CUp.elem[1] = camera.elem[1][1];
	CUp.elem[2] = camera.elem[1][2];

	CLook.elem[0] = camera.elem[2][0];
	CLook.elem[1] = camera.elem[2][1];
	CLook.elem[2] = camera.elem[2][2];

	CPos.elem[0] = camera.elem[3][0];
	CPos.elem[1] = camera.elem[3][1];
	CPos.elem[2] = camera.elem[3][2];

	valX = vector::vector_3x::DotProduct(CPos, CRight);
	valY = vector::vector_3x::DotProduct(CPos, CUp);
	valZ = vector::vector_3x::DotProduct(CPos, CLook);

	R.elem[0][0] = camera.elem[0][0];
	R.elem[0][1] = camera.elem[1][0];
	R.elem[0][2] = camera.elem[2][0];
	R.elem[0][3] = 0.0f;

	R.elem[1][0] = camera.elem[0][1];
	R.elem[1][1] = camera.elem[1][1];
	R.elem[1][2] = camera.elem[2][1];
	R.elem[1][3] = 0.0f;

	R.elem[2][0] = camera.elem[0][2];
	R.elem[2][1] = camera.elem[1][2];
	R.elem[2][2] = camera.elem[2][2];
	R.elem[2][3] = 0.0f;

	R.elem[3][0] = -valX;
	R.elem[3][1] = -valY;
	R.elem[3][2] = -valZ;
	R.elem[3][3] = 1.0f;
}