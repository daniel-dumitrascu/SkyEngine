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

void TexRes::Add(Texture* texture, int key)
{
	MapCollection::Add(texture, key);
}

void TexRes::Remove(const int index)
{
	MapCollection::Remove(index);
}

bool TexRes::Find(const int index)
{
	return MapCollection::Find(index);
}

Texture* TexRes::Retrive(const int index)
{
	return MapCollection::Retrive(index);
}
		