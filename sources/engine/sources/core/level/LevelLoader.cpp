#include "LevelLoader.h"
#include "utils/Utils.h"
#include "parser/FileLevel.h"
#include "LevelData.h"


LevelLoader* LevelLoader::GetInstance()
{
	static LevelLoader instance;
	return &instance;
}

LevelLoader::LevelLoader() : log("LevelLoader")
{
}

void* LevelLoader::Load(const std::string& file_path)
{
	void* m_buffer = nullptr;

	std::string extension = utils::str::GetFileExtension(file_path);

	if (extension == "level")
	{
		FileLevel* parser = FileLevel::GetInstance();
		m_buffer = parser->ParseFile(file_path);
	}
	else
	{
		log.message("Level file type is not recognised!", Logging::MSG_ERROR);
		exit(1);
	}
	
	if (m_buffer == nullptr)
	{
		log.message("Level file could not be loaded!", Logging::MSG_ERROR);
		exit(1);
	}

	return m_buffer;
}