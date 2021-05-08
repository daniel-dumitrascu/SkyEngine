#ifndef CORE_UTILS
#define CORE_UTILS

#include <string>

namespace utils
{

	namespace path
	{
		void GetWorkingDir(std::string& _path);
	}

	namespace str
	{
		const char* Strfmt(const char* fmt, ...);
		std::string GetFileExtension(const std::string s);
	}
}


#endif