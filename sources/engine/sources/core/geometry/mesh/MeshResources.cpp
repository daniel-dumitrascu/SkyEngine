#include "MeshResources.h"
#include "geometry/mesh/MeshLoader.h"

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

void MeshRes::Add(const std::string& key, const std::string pathToResource)
{
	WireFrame* wireframe = (WireFrame*)MeshLoader::GetInstance()->Load(pathToResource);

	if(wireframe)
		MapPtrCollection::Add(wireframe, key);
}

void MeshRes::Remove(const std::string& key)
{
	MapPtrCollection::Remove(key);
}

unsigned int MeshRes::Count()
{
	return MapPtrCollection::Count();
}

bool MeshRes::Find(const std::string& key)
{
	return MapPtrCollection::Find(key);
}

WireFrame* MeshRes::Retrive(const std::string& key)
{
	return MapPtrCollection::Retrive(key);
}
