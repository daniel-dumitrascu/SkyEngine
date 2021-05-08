#ifndef PAINTER
#define PAINTER

#include "../geometry/mesh/WireFrame.h"


class Painter
{
	public:

		static Painter* GetInstance()
		{
			static Painter instance;
			return (&instance);
		};

		void SelectShader(const unsigned int shader_pair_id);
		void static SetActiveTexture(const unsigned int tex_location, const char* tex_name);

		void static SendGeometryToGPU(WireFrame* mesh);
		void static RemoveGeometryFromGPU(WireFrame* mesh);

		unsigned int GetMeshLocation();
		unsigned int GetTexLocation();
		unsigned int GetColorLocation();
		unsigned int GetMemoryLocation();

		void static EnableTextureLocation(const unsigned int tex_loc);
		void static EnableMeshLocation(const unsigned int mesh_loc);

		void static SetBindTexture(const unsigned int id);
		void static SetStartDrawData(const unsigned int mem_loc, int mem_hop, int data);
		void static SetDrawMatrix4Data(const unsigned int mem_loc, const float* matrix_data);
		void static SetDrawColorData(const unsigned int mem_loc, const float* color_data);
		void static ClearScreen();
		void static DrawData(const int inx_count);

		void static SelectArrayBuffer(unsigned int buff_id);
		void static SelectIndxBuffer(unsigned int buff_id);

	private:

		Painter();
		Painter(const Painter& copy) {};
		~Painter() {};

	private:

		int m_mesh_location;
		int m_texture_location;
		int m_color_location;
		int m_wpmatrix_location;
};


#endif