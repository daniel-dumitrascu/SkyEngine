#include "AnimDataLoader.h"
#include "utils/Utils.h"
#include "parser/FileAnim.h"


AnimDataLoader* AnimDataLoader::GetInstance()
{
	static AnimDataLoader instance;
	return &instance;
}

AnimDataLoader::AnimDataLoader() : log("AnimDataLoader")
{
}

void* AnimDataLoader::Load(const std::string& file_path)
{
	void* m_buffer = NULL;

	std::string extension = utils::str::GetFileExtension(file_path);

	if (extension == "anim")
	{
		FileAnim* obj = FileAnim::GetInstance();
		m_buffer = obj->ParseFile(file_path);
	}
	else
	{
		log.message("Anim file type is not recognised!", Logging::MSG_ERROR);
		exit(1);
	}

	if (m_buffer == NULL)
	{
		log.message("Anim file could not be loaded!", Logging::MSG_ERROR);
		exit(1);
	}

	return m_buffer;
}