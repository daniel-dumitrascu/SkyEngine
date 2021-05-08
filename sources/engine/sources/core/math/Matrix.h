#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"


#define  MAX_COL_3X   3
#define  MAX_ROW_3X   3

#define  MAX_COL_4X   4
#define  MAX_ROW_4X   4



struct mat_3x
{
	float elem[3][3];
};



struct mat_4x
{
	float elem[4][4];
};



namespace matrix
{

	namespace matrix_3x
	{
	 
		// Set a 3x3 matrix
		void SetMatrix(mat_3x& R, const mat_3x& A);
		void SetMatrix(mat_3x& R, const float m01, const float m02, const float m03,
								  const float m04, const float m05, const float m06,
								  const float m07, const float m08, const float m09);
	  
		// Set a 3x3 identity matrix 
		void SetIdentity(mat_3x& R);

		// Addition 3x3 matrix
		void Addition(mat_3x& R, const mat_3x& A);

		// Subtraction 3x3 matrix
		void Subtraction(mat_3x& R, const mat_3x& A);

		// Multiply 3x3 matrix or scalar
		void Multiply(mat_3x& R, const mat_3x& A, const float scalar);
		void Multiply(mat_3x& Out, const mat_3x& A, const mat_3x& B);
		void Multiply(vec_3x& Out, const vec_3x& vec, const mat_3x& mat);

		// Determinant 3x3
		float Determinant(const mat_3x& mat);

		// Transpoze or 3x3
		void Transpoze(mat_3x& R);

		// Inverse 3x3
		void Inverse(mat_3x& R);

		// Adjugate 3x3
		void Adjugate(mat_3x& R);

		// Print 3x3
		void PrintIt(const mat_3x& R);

		// Minor 2x2
		float Minor(const float m01, const float m02, const float m03, const float m04);
	}

	namespace matrix_4x
	{
		 // Set a 4x4 matrix
		 void SetMatrix(mat_4x& R, const mat_4x& A);

		 // Set a 4x4 matrix
	     void SetMatrix(mat_4x& R, const float m01, const float m02, const float m03, const float m04, 
						    	   const float m05, const float m06, const float m07, const float m08, 
								   const float m09, const float m10, const float m11, const float m12, 
								   const float m13, const float m14, const float m15, const float m16);	
		
		 // Set a 4x4 identity matrix 
		 void SetIdentity(mat_4x& R);

		 // Addition 4x4 matrix
		 void Addition(mat_4x& R, const mat_4x& A, const mat_4x& B);

		 // Subtraction 4x4 matrix
		 void Subtraction(mat_4x& R, const mat_4x& A, const mat_4x& B);

		 // Multiply 4x4 matrix or scalar
		 void Multiply(mat_4x& R, const mat_4x& A, const float scalar);
		 void Multiply(mat_4x& R, const mat_4x& A, const mat_4x& B);
		 void Multiply(vec_4x& R, const vec_4x& vec, const mat_4x& mat);

		 float Minor(const float m01, const float m02, const float m03, 
					 const float m04, const float m05, const float m06,
					 const float m07, const float m08, const float m09);

		 // Determinant 4x4
	     float Determinant(const mat_4x& mat);

		 // Transpoze or 4x4
		 void Transpoze(mat_4x& R, const mat_4x& to_trans);

		 // Inverse 4x4
		 void Inverse(mat_4x& R, const mat_4x& to_inv);

		 // Adjugate 4x4
		 void Adjugate(mat_4x& R, const mat_4x& A);

		 // Print 4x4
		 void PrintIt(mat_4x& R);
	}

	namespace game_matrix
	{
		void SetWorldScale(mat_4x& R, const float scale);

		/* Set position and rotation in world game matrix */
		void SetWorldPosAndRot(mat_4x& R, const vec_3x& pos, const vec_3x& rot);

		/* Set position and rotation in world game matrix */
		void SetWorldPosAndRot(mat_4x& R, const float rotX, const float rotY, const float rotZ,
							              const float pozX, const float pozY, const float pozZ);

		/* Set position in world game matrix */
		void SetWorldPosition(mat_4x& R, const vec_3x& pos);

		/* Set position in world game matrix */
		void SetWorldPosition(mat_4x& R, const float pos_x, const float pos_y, const float pos_z);

		/* Set rotation in world game matrix */
		void SetWorldRotation(mat_4x& R, const float pos_x, const float pos_y, const float pos_z);

		/* Set rotation in world game matrix */
		void SetWorldRotation(mat_4x& R, const vec_3x& rot);

		/* Projection matrix */
		void ProjectionMatrix(mat_4x& R, const float left, const float right, const float bottom, 										 
										 const float top, const float near, const float far);

		/* World-Projection matrix */
		void WorldProjMatrix(mat_4x& R, const mat_4x& world, const mat_4x& proj);
	}
}


#endif