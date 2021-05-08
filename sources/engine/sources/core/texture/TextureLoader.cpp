#include "TextureLoader.h"
#include "utils/Utils.h"
#include "texture/formats/FileTGA.h"
#include "texture/formats/FilePNG.h"


TexLoader* TexLoader::GetInstance()
{
	static TexLoader instance;
	return &instance;
}

TexLoader::TexLoader() : log("TexLoader")
{
}

void* TexLoader::Load(const std::string& file_path)
{
	void* m_buffer = NULL;

	std::string extension = utils::str::GetFileExtension(file_path);

	if(extension == "tga")
	{
		m_buffer = FileTGA::GetInstance()->LoadTGA(file_path);
	}
	else if (extension == "png")
	{
		m_buffer = FilePNG::GetInstance()->LoadPNG(file_path);
	}
	else
	{
		log.message("Texture file type is not recognised!", Logging::MSG_ERROR);
		exit(1);
	}

	if (m_buffer == NULL)
	{
		log.message("Texture file could not be loaded!", Logging::MSG_ERROR);
		exit(1);
	}

	m_is_loaded = true;
	return m_buffer;
}