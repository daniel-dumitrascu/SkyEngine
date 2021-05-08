#ifndef OPENGL2SHADER
#define OPENGL2SHADER

#include <iostream>
#include <string>
#include "stream/Stream.h"
#include "../Shader.h"
#include "logging/Logging.h"

class OpenGL2File : private Stream
{
	public:

		static OpenGL2File* GetInstance();
		ShaderPair* LoadGL2ShaderPair(const std::string& file_path);

	private:

		OpenGL2File();
		OpenGL2File(const OpenGL2File& copy) = delete;
		~OpenGL2File() {};

		unsigned int LoadShader(const std::string& file_path, const int type);
		unsigned int CompileShader(const int type, const char* shader_buffer);

		void Write(const void* buffer, int size){};

		Logging log;
};

#endif