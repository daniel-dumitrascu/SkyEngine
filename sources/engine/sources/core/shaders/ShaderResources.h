#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include "utils/MapCollection.h"
#include "Shader.h"
#include "logging/Logging.h"


class ShaderRes : private MapPtrCollection<unsigned int>
{
	public:

		static ShaderRes* GetInstance();
		
		bool Add(const std::string& key, const std::string pathToResource);
		void Remove(const std::string& key);
		unsigned int CountShaderPair();
		bool ExistShaderPair(const std::string& key);
		unsigned int Retrive(const std::string& key);

	private:

		ShaderRes();
		ShaderRes(const ShaderRes& copy) = delete;
		~ShaderRes();

		ShaderRes& operator = (const ShaderRes& copy) {};

		/* A valid (!= -1) program id is returned by this function */
		unsigned int CompileShaderPair(unsigned int v_shader, unsigned int f_shader);
		bool LinkShaderPairProgram(unsigned int program_id);
		Logging log;
};

#endif