#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "loader/Loader.h"
#include "logging/Logging.h"

class MeshLoader : public Loader
{

public:

	static MeshLoader* GetInstance();
	void* Load(const std::string& file_path);

private:

	MeshLoader();
	MeshLoader(const MeshLoader& copy) = delete;
	~MeshLoader() {};

	MeshLoader& operator = (const MeshLoader& copy) {};

	Logging log;
};

#endif