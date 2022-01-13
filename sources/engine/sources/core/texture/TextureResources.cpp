#include "TextureResources.h"
#include "texture/TextureLoader.h"

TexRes* TexRes::GetInstance()
{
	static TexRes instance;
	return &instance;
}

TexRes& TexRes::operator=(const TexRes& copy)
{
	//TODO 
	return *this;
}

void TexRes::Add(const std::string& key, const std::string pathToResource)
{
	Texture* texture = (Texture*)TexLoader::GetInstance()->Load(pathToResource);

	if (texture)
		MapPtrCollection::Add(texture, key);
}

void TexRes::Remove(const std::string& key)
{
	MapPtrCollection::Remove(key);
}

bool TexRes::Find(const std::string& key)
{
	return MapPtrCollection::Find(key);
}

Texture* TexRes::Retrive(const std::string& key)
{
	return MapPtrCollection::Retrive(key);
}
		