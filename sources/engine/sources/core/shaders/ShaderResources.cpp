#include "ShaderResources.h"
#include "ShaderLoader.h"
#include "../core/global/GlobalPaths.h"
#include "../video/GraphicHeaders.h"


ShaderRes* ShaderRes::GetInstance()
{
	static ShaderRes instance;
	return &instance;
}

ShaderRes::ShaderRes() : log("ShaderRes")
{
}

ShaderRes::~ShaderRes()
{
	std::map<const std::string, unsigned int>::iterator  ite = m_collection.begin();

	for (; ite != m_collection.end();)
	{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
		glDeleteProgram(ite->second);
#endif
		const std::string& to_del = ite->first;
		++ite;
		Remove(to_del);
	}
}

bool ShaderRes::AddShaderPair(ShaderPair* shaderPair, const std::string& key)
{
	if (shaderPair)
	{
		unsigned int program_id = CompileShaderPair(shaderPair->m_vertexShader.m_shaderID, shaderPair->m_fragmentShader.m_shaderID);
		
		if (program_id != -1)
		{
			MapCollection::Add(program_id, key);
			return true;
		}
	}

	return false;
}

void ShaderRes::RemoveShaderPair(const std::string& key)
{
	//TODO if this function is called many times, an optimization would be to use an iterator as in ShaderRes :: ~ ShaderRes ()
	unsigned int program_id = RetriveProgramID(key);

	//TODO also read the link saved https://www.opengl.org/discussion_boards/showthread.php/181432-Correct-way-to-delete-shader-programs

	if (program_id)
	{
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
		glDeleteProgram(program_id);
#endif
	}

	MapCollection::Remove(key);
}

unsigned int ShaderRes::CountShaderPair()
{
	return MapCollection::Count();
}

bool ShaderRes::ExistShaderPair(const std::string& key)
{
	return MapCollection::Find(key);
}

unsigned int ShaderRes::RetriveProgramID(const std::string& key)
{
	return MapCollection::Retrive(key);
}

unsigned int ShaderRes::CompileShaderPair(unsigned int v_shader, unsigned int f_shader)
{
	if (v_shader && f_shader)
	{
		unsigned int program_id = -1;

		/* Create the program object */
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
		program_id = glCreateProgram();
#endif

		if (program_id == 0)
		{
			log.message("Can't create shader pair program ID!", Logging::MSG_ERROR);
			exit(1);
		}

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
		glAttachShader(program_id, v_shader);
		glAttachShader(program_id, f_shader);


		if (!LinkShaderPairProgram(program_id))
		{
			log.message("Can't link the program!", Logging::MSG_ERROR);
			exit(1);
		}

		glDetachShader(program_id, v_shader);
		glDetachShader(program_id, f_shader);
		glDeleteShader(v_shader);
		glDeleteShader(f_shader);
#endif

		return program_id;
	}

	return -1;
}

bool ShaderRes::LinkShaderPairProgram(unsigned int program_id)
{

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	GLint  linked;

	/* Link the program */
	glLinkProgram(program_id);

	/* Check the link status */
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];

			glGetProgramInfoLog(program_id, infoLen, NULL, infoLog);
			std::string msg = "linking program: ";
			msg += infoLog;
			log.message(msg, Logging::MSG_INFO);
			delete infoLog;
		}

		/* Clean up */
		glDeleteProgram(program_id);
		return false;
	}
#endif

	return true;
}