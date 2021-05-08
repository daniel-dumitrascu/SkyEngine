#include "Painter.h"
#include <iostream>
#include "../video/GraphicHeaders.h"



Painter::Painter() : m_mesh_location(-1),
					 m_texture_location(-1),
					 m_color_location(-1),
					 m_wpmatrix_location(-1)
{

}

void Painter::SelectShader(const unsigned int shader_pair_id)
{
	//TODO That's what I've though too, group the objects that use the same shader to be drawn one after the other.
	//TODO each time I start drawing with a new pair of shaders I will add this call in Draw scheme (in PostDraw)

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glUseProgram(shader_pair_id);

	m_mesh_location = glGetAttribLocation(shader_pair_id, "aPosition");
	
	//TODO - format the error accordingly 
	//if (m_mesh_location < 0)
	//	std::cout << "glGetAttribLocation error, <aPosition> not found ..." << std::endl;

	m_texture_location = glGetAttribLocation(shader_pair_id, "aTexture");

	//TODO - format the error accordingly 
	//if (m_texture_location < 0)
	//	std::cout << "glGetAttribLocation error, <aTexture> not found ..." << std::endl;

	m_color_location = glGetUniformLocation(shader_pair_id, "vColor");

	//TODO - format the error accordingly 
	//if (m_color_location < 0)
	//	std::cout << "glGetUniformLocation error, <vColor> not found ..." << std::endl;

	m_wpmatrix_location = glGetUniformLocation(shader_pair_id, "proj");

	//TODO - format the error accordingly 
	//if (m_wpmatrix_location < 0)
	//	std::cout << "glGetUniformLocation error, <proj> not found ..." << std::endl;
#endif
}

void Painter::SendGeometryToGPU(WireFrame* mesh)
{
	if (mesh && !mesh->IsGeometryInGPU())
	{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
		unsigned int vbo_vert;
		glGenBuffers(1, &vbo_vert);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* mesh->GetGeometryCount(), mesh->GetModelStartData(), GL_STATIC_DRAW);
		mesh->SetVBOVert(vbo_vert);

		unsigned int vbo_indx;
		glGenBuffers(1, &vbo_indx);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indx);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)* mesh->GetGeometryCount(), mesh->GetIndices(), GL_STATIC_DRAW);
		mesh->SetVBOIndx(vbo_indx);
#endif

		mesh->SetGeometryInGPU(true);
	}
}

void Painter::RemoveGeometryFromGPU(WireFrame* mesh)
{
	if (mesh && mesh->IsGeometryInGPU())
	{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
		unsigned int vbo_vert = mesh->GetVBOVert();
		glDeleteBuffers(1, &vbo_vert);
		unsigned int vbo_indx = mesh->GetVBOIndx();
		glDeleteBuffers(1, &vbo_indx);
#endif
		mesh->SetGeometryInGPU(false);
	}
}

unsigned int Painter::GetMeshLocation()
{
	return m_mesh_location;
}

void Painter::EnableTextureLocation(const unsigned int tex_loc)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glEnableVertexAttribArray(tex_loc);
#endif
}

unsigned int Painter::GetMemoryLocation()
{
	return m_wpmatrix_location;
}

void Painter::EnableMeshLocation(const unsigned int mesh_loc)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glEnableVertexAttribArray(mesh_loc);
#endif
}

unsigned int Painter::GetTexLocation()
{
	return m_texture_location;
}

unsigned int Painter::GetColorLocation()
{
	return m_color_location;
}

void Painter::SetActiveTexture(const unsigned int shader_pair_id, const char* tex_name)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glActiveTexture(GL_TEXTURE0); //TODO warning, this may not work with models that hame multiple textures
	glUniform1i(glGetUniformLocation(shader_pair_id, tex_name), 0); // TODO warning, I can do this only to the scene objects that use the same shader pair
#endif
}

void Painter::SetBindTexture(const unsigned int id)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glBindTexture(GL_TEXTURE_2D, id);
#endif
}

void Painter::SetStartDrawData(const unsigned int mem_loc, int mem_hop, int data)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glVertexAttribPointer(mem_loc, 2, GL_FLOAT, GL_FALSE, mem_hop, (const void*)data);
#endif
}

void Painter::SetDrawMatrix4Data(const unsigned int mem_loc, const float* matrix_data)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glUniformMatrix4fv(mem_loc, 1, GL_FALSE, matrix_data);
#endif
}

void Painter::SetDrawColorData(const unsigned int mem_loc, const float* color_data)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glUniform4fv(mem_loc, 1, color_data);
#endif
}

void Painter::DrawData(const int inx_count)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glDrawElements(GL_TRIANGLES, inx_count, GL_UNSIGNED_SHORT, (const void*)0);
#endif
}

void Painter::SelectArrayBuffer(unsigned int buff_id)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glBindBuffer(GL_ARRAY_BUFFER, buff_id);
#endif
}

void Painter::SelectIndxBuffer(unsigned int buff_id)
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff_id);
#endif
}

void Painter::ClearScreen()
{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	glClear(GL_COLOR_BUFFER_BIT);
#endif
}
