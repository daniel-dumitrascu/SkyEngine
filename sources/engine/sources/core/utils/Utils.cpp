#include "Utils.h"

#include <iostream>

#if(WINDOWS_PLATFORM)
	#include <Windows.h>
	#define MAX_PATH_LEN    1024
#elif(LINUX_PLATFORM)
	#include <unistd.h>
	#include <limits.h>
	#include <stdarg.h>
#endif

#define MAX_STRING_LEN  2048

void utils::path::GetWorkingDir(std::string& path)
{
#if(WINDOWS_PLATFORM)
	char _path[MAX_PATH_LEN];
	GetCurrentDirectory(MAX_PATH_LEN, _path);
	path = _path;
#elif(LINUX_PLATFORM)
	char _path[PATH_MAX];
	if(getcwd(_path, PATH_MAX) != NULL)
	{
		path = _path;
	}
#endif
}

const char* utils::str::Strfmt(const char* fmt, ...)
{
	static char s_stringBuf[MAX_STRING_LEN];  // enough? safe?

	va_list args;
	va_start(args, fmt);

	vsnprintf(s_stringBuf, MAX_STRING_LEN, fmt, args);

	va_end(args);
	return (const char*)s_stringBuf;
}

std::string utils::str::GetFileExtension(const std::string file)
{
	int pos = file.length() - 1;
	std::string extension;

	while (pos && file[pos] != '.')
		--pos;

	/* We only take the extension if it is one */
	if (pos > 0)
		extension = file.c_str() + (pos + 1);

	return extension;
}