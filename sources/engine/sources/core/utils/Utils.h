#ifndef CORE_UTILS
#define CORE_UTILS

#include <string>

namespace utils
{

	namespace path
	{
		void GetWorkingDir(std::string& _path);

		bool IsFileCreated(const std::string& _path, const std::string& _fileName);

		std::ofstream CreateFileAtLocation(const std::string& _path, const std::string& _fileName);
	}

	namespace str
	{
		const char* Strfmt(const char* fmt, ...);
		std::string GetFileExtension(const std::string s);
	}
}


#endif