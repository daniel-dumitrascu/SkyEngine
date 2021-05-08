#ifndef SHADER_H
#define SHADER_H

struct Shader
{
	Shader() : m_shaderID(0) {}

	unsigned int m_shaderID;
};


struct ShaderPair
{
	Shader m_vertexShader;
	Shader m_fragmentShader;
};

#endif