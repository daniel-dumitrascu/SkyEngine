#ifndef FILE_LEVEL
#define FILE_LEVEL

#include "stream/Stream.h"
#include "../LevelData.h"

class FileLevel : private Stream
{
	public:

		static FileLevel* GetInstance();
		LevelPackage* ParseFile(const std::string& file_path);

	private:

		FileLevel() {};
		FileLevel(const FileLevel& copy) {};
		~FileLevel() {};
};


#endif