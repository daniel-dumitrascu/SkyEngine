#ifndef VECTOR_H
#define VECTOR_H


struct vec_2x
{
	vec_2x()
	{ }

	vec_2x(const float x, const float y)
	{
		elem[0] = x;
		elem[1] = y;
	}

	bool operator==(const vec_2x& ref)
	{
		return (elem[0] == ref.elem[0]) && (elem[1] == ref.elem[1]);
	}

	float elem[2];
};

struct vec_3x
{
	vec_3x()
	{ }

	vec_3x(const float x, const float y, const float z)
	{
		elem[0] = x;
		elem[1] = y;
		elem[2] = z;
	}

	bool operator==(const vec_3x& ref)
	{
		return (elem[0] == ref.elem[0]) && 
			   (elem[1] == ref.elem[1]) &&
			   (elem[2] == ref.elem[2]);
	}

	float elem[3];
};


struct vec_4x
{
	vec_4x()
	{ }

	vec_4x(const float x, const float y, const float z, const float t)
	{
		elem[0] = x;
		elem[1] = y;
		elem[2] = z;
		elem[3] = t;
	}

	bool operator==(const vec_3x& ref)
	{
		return (elem[0] == ref.elem[0]) &&
			   (elem[1] == ref.elem[1]) &&
			   (elem[2] == ref.elem[2]) &&
			   (elem[3] == ref.elem[3]);
	}

	float elem[4];
};



namespace vector
{
	namespace vector_2x
	{
		// Set a vector of size 2
		void SetVector(vec_2x& R, const float vec_x, const float vec_y);
		void SetVector(vec_2x& R, const vec_2x& A);

		// Subtraction 2D vectors
		void Subtraction(vec_2x& R, const vec_2x& A, const vec_2x& B);

		// Magnitude
		float Magnitude(const vec_2x& A);

		// Normalization
		void Normalization(vec_2x& R, const vec_2x& vector);

		// Get a perpendicular vector
		void Perpendicular(vec_2x& R, const vec_2x& vector);
	}

	namespace vector_3x
	{
		// Set a vector of size 3
	   void SetVector(vec_3x& R, const float vec_x, const float vec_y, const float vec_z);
	   void SetVector(vec_3x& R, const vec_3x& A);


	   // Addition 2D 3D or 4D vectors
	   void Addition(vec_3x& R, const vec_3x& A, const vec_3x& B);


	   // Subtraction 3D vectors
	   void Subtraction(vec_3x& R, const vec_3x& A, const vec_3x& B);


	   // Dot Product - make acos() of the rezult and compute the angle
	   float DotProduct(const vec_3x& A, const vec_3x& B);
	   void  DotProduct(vec_3x& R, const vec_3x& A, const float scalar);

	   // See if a vector is equal with another
	   bool IsEqual(const vec_3x& A, const vec_3x& B);


	   // Magnitude
	   float Magnitude(const vec_3x& A);


	   // Cross Product
	   void CrossProduct(vec_3x& R, const vec_3x& A, const vec_3x& B);


	   // Normalization
	   void Normalization(vec_3x& R, const vec_3x& vector);


	   // Angle between 2 vectors in radians
	   float AngleBetwVec(const vec_3x& A, const vec_3x& B);

	   // Vector projection onto another
	   void VectorProjection(vec_3x& R, const vec_3x& proj, const vec_3x& onto);
	}

	namespace vector_4x
	{

	   // Set a vector of size 4
	   void  SetVector(vec_4x& R, const float vec_x, const float vec_y, const float vec_z, const float vec_w);
	   void  SetVector(vec_4x& R, const vec_4x& A);


	   // Addition 2D 3D or 4D vectors
	   void Addition(vec_4x& R, const vec_4x& A, const vec_4x& B);


	   // Subtraction 2D 3D or 4D vectors
	   void Subtraction(vec_4x& R, const vec_4x& A, const vec_4x& B);


	   // Dot Product - make acos() of the rezult and compute the angle
	   float DotProduct(const vec_4x& A, const vec_4x& B);
	   void  DotProduct(vec_4x& R, const vec_4x& vector, const float scalar);


	   // See if a vector is equal with another
	   bool IsEqual(const vec_4x& A, const vec_4x& B);


	   // Magnitude
	   float Magnitude(const vec_4x& A);


	   // Normalization
	   void Normalization(vec_4x& R, const vec_4x& vector);


	   // Angle between 2 vectors in radians
	   float AngleBetwVec(const vec_4x& A, const vec_4x& B);


	   // Vector projection onto another
	   void VectorProjection(vec_4x& R, const vec_4x& proj, const vec_4x& onto);
	}

	namespace vector_game
	{

		/* Convert screen to world coordonates */
		void ScreenToWorld(const vec_3x screen_pos, vec_3x& world_pos,
						   const float world_width_right, const float world_height_down,
						   const float screen_w, const float screen_h);

		/* Convert world to screen */
		void WorldToScreen(const vec_3x world_pos, vec_3x& screen_pos,
						   const float world_width_right, const float world_height_down,
						   const float screen_w, const float screen_h);

		/* Convert world to screen */
		void WorldToScreen(const float world_pos_x, const float world_pos_y, 
			               float& screen_pos_x, float& screen_pos_y,
			               const float world_width_right, const float world_height_down,
			               const float screen_w, const float screen_h);
	}
}



#endif