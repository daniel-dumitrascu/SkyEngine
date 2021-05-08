#ifndef SHADER_LOADER
#define SHADER_LOADER

#include "loader/Loader.h"
#include "Shader.h"
#include "logging/Logging.h"

//TODO https://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/BestPracticesforShaders/BestPracticesforShaders.html#//apple_ref/doc/uid/TP40008793-CH7-SW3

class ShaderLoader : public Loader
{

public:

	static ShaderLoader* GetInstance();
	void* Load(const std::string& file_path);

private:

	ShaderLoader();
	ShaderLoader(const ShaderLoader& copy) = delete;
	~ShaderLoader() {};

	ShaderLoader& operator = (const ShaderLoader& copy) {};

	Logging log;
};

#endif