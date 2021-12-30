#include "MeshLoader.h"
#include "utils/Utils.h"
#include "parser/FileMesh.h"


MeshLoader* MeshLoader::GetInstance()
{
	static MeshLoader instance;
	return &instance;
}

MeshLoader::MeshLoader() : log("MeshLoader")
{
}

void* MeshLoader::Load(const std::string& file_path)
{
	void* m_buffer = NULL;

	std::string extension = utils::str::GetFileExtension(file_path);

	if (extension == "mesh")
	{
		FileMesh* obj = FileMesh::GetInstance();
		m_buffer = obj->ParseFile(file_path);
	}
	else
	{
		log.message("Model file type is not recognised!", Logging::MSG_ERROR);
		exit(1);
	}

	if (m_buffer == NULL)
	{
		log.message("Mesh file could not be loaded!", Logging::MSG_ERROR);
		exit(1);
	}

	return m_buffer;
}