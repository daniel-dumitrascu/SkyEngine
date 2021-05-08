#include "IClearFile.h"

#if(LINUX_PLATFORM)
#include <string.h> // Added for strlen
#endif

IClearFile::IClearFile(const char* _path)
{
	Open(_path, std::ios_base::in);
}

IClearFile::IClearFile(const std::string& _path)
{
	Open(_path, std::ios_base::in);
}

IClearFile::~IClearFile()
{
	Close();
}

void IClearFile::Read(void* buffer, int size)
{
	m_file_stream->read((char*)buffer, size);
	((char*)buffer)[size] = '\0';
}

std::fstream& operator >>(IClearFile& file, char* message)
{
	file.Read(message, strlen(message));
	return *(file.m_file_stream);
}