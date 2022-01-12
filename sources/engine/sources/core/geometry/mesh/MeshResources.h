#ifndef MESH_RESOURCES_H
#define MESH_RESOURCES_H

#include "utils/MapCollection.h"
#include "WireFrame.h"

class MeshRes : private MapPtrCollection<WireFrame>
{
public:

	static MeshRes* GetInstance();

	void Add(WireFrame* mesh, const std::string& key);
	void Remove(const std::string& key);
	unsigned int Count();
	bool Find(const std::string& key);
	WireFrame* Retrive(const std::string& key);

private:

	MeshRes();
	MeshRes(const MeshRes& copy);
	~MeshRes();

	MeshRes& operator=(const MeshRes& copy);
};

#endif