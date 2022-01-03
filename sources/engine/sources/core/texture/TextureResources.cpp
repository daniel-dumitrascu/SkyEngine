#include "TextureResources.h"

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

void TexRes::Add(Texture* texture, const std::string& key)
{
	MapCollection::Add(texture, key);
}

void TexRes::Remove(const std::string& key)
{
	MapCollection::Remove(key);
}

bool TexRes::Find(const std::string& key)
{
	return MapCollection::Find(key);
}

Texture* TexRes::Retrive(const std::string& key)
{
	return MapCollection::Retrive(key);
}
		