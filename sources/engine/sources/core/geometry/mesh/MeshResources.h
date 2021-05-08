#ifndef MESH_RESOURCES_H
#define MESH_RESOURCES_H

#include "utils/MapCollection.h"
#include "WireFrame.h"

class MeshRes : private MapCollection<WireFrame*>
{
public:

	static MeshRes* GetInstance();

	void Add(WireFrame* mesh, int key);
	void Remove(const int index);
	unsigned int Count();
	bool Find(const int index);
	WireFrame* Retrive(const int index);

private:

	MeshRes();
	MeshRes(const MeshRes& copy);
	~MeshRes();

	MeshRes& operator=(const MeshRes& copy);
};

#endif