#include "MeshResources.h"

MeshRes* MeshRes::GetInstance()
{
	static MeshRes instance;
	return &instance;
}

MeshRes::MeshRes()
{

}

MeshRes::MeshRes(const MeshRes& copy)
{
	//TODO
}

MeshRes::~MeshRes()
{

}

MeshRes& MeshRes::operator=(const MeshRes& copy)
{
	//TODO
	return *this;
}

void MeshRes::Add(WireFrame* mesh, int key)
{
	MapCollection::Add(mesh, key);
}

void MeshRes::Remove(const int index)
{
	MapCollection::Remove(index);
}

unsigned int MeshRes::Count()
{
	return MapCollection::Count();
}

bool MeshRes::Find(const int index)
{
	return MapCollection::Find(index);
}

WireFrame* MeshRes::Retrive(const int index)
{
	return MapCollection::Retrive(index);
}
