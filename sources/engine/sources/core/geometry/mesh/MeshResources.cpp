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

void MeshRes::Add(WireFrame* mesh, const std::string& key)
{
	MapCollection::Add(mesh, key);
}

void MeshRes::Remove(const std::string& key)
{
	MapCollection::Remove(key);
}

unsigned int MeshRes::Count()
{
	return MapCollection::Count();
}

bool MeshRes::Find(const std::string& key)
{
	return MapCollection::Find(key);
}

WireFrame* MeshRes::Retrive(const std::string& key)
{
	return MapCollection::Retrive(key);
}
