#include "ShaderLoader.h"

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	#include "language/OpenGL2File.h"
#elif(DIRECTX_GRAPHICS)
	#include "language/DirectXShader.h"
#endif

ShaderLoader* ShaderLoader::GetInstance()
{
	static ShaderLoader instance;
	return &instance;
}

ShaderLoader::ShaderLoader() : log("ShaderLoader")
{
}

void* ShaderLoader::Load(const std::string& file_path)
{
	void* m_buffer = nullptr;

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	m_buffer = OpenGL2File::GetInstance()->LoadGL2ShaderPair(file_path);
#elif(DIRECTX_GRAPHICS)
	m_buffer = DirectXFile::GetInstance()->LoadDirectXShader(file_path);
#endif

	if (m_buffer)
		return m_buffer;

	log.message("Shader file could not be loaded!", Logging::MSG_ERROR);
	exit(1);
}