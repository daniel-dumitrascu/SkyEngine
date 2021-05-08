#include "OpenGL2File.h"
#include "../../video/GraphicHeaders.h"
#include "utils/Utils.h"
#include <vector>

OpenGL2File* OpenGL2File::GetInstance()
{
	static OpenGL2File instance;
	return &instance;
} 

OpenGL2File::OpenGL2File() : log("OpenGL2File")
{
}

ShaderPair* OpenGL2File::LoadGL2ShaderPair(const std::string& file_path)
{
	ShaderPair* result = NULL;

	/* Create 2 paths for the vertex and fragment shaders */
	const std::string vertexShaderPath(file_path + ".vshader");
	const std::string fragmentShaderPath(file_path + ".fshader");

	unsigned int vertexID = LoadShader(vertexShaderPath, GL_VERTEX_SHADER);
	unsigned int fragmentID = LoadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	if (vertexID && fragmentID)
	{
		result = new ShaderPair;
		result->m_vertexShader.m_shaderID = vertexID;
		result->m_fragmentShader.m_shaderID = fragmentID;
	}

	return result;
}

unsigned int OpenGL2File::LoadShader(const std::string& file_path, const int type)
{
	int shader_id = 0;

	/* Open the file */
	Open(file_path, std::ios::in);

	if (IsOpen())
	{
		/* Read the whole file into memory */
		char* buffer = new char[m_file_size + 1]();
		Read(buffer, m_file_size);
		Close();

		/* Compile shader */
		shader_id = CompileShader(type, buffer);

		delete[] buffer;
	}

	return shader_id;
}

unsigned int OpenGL2File::CompileShader(const int type, const char* shader_buffer)
{
	GLuint shader_id = glCreateShader(type);

	if (shader_id)
	{
		// Load the shader source
		glShaderSource(shader_id, 1, &shader_buffer, NULL);

		// Compile the shader
		glCompileShader(shader_id);

		GLint  success;

		// Check the compile status
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			//Setup Error Log
			GLint maxLength = 0;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(shader_id, maxLength, &maxLength, &errorLog[0]);
			std::string msg;
			for (int i = 0; i < errorLog.size(); i++) {
				msg += errorLog[i];
			}
			log.message(msg, Logging::MSG_ERROR);
			glDeleteShader(shader_id);
			shader_id = 0;
		}
	}
		
	return shader_id;
}