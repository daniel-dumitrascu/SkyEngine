#include "AnimDataResources.h"

AnimDataRes* AnimDataRes::GetInstance()
{
	static AnimDataRes instance;
	return &instance;
}

AnimDataRes& AnimDataRes::operator=(const AnimDataRes& copy)
{
	//TODO
	return *this;
}

void AnimDataRes::Add(AnimData* anim, const std::string& key)
{
	MapPtrCollection::Add(anim, key);
}

void AnimDataRes::Remove(const std::string& key)
{
	MapPtrCollection::Remove(key);
}

unsigned int AnimDataRes::Count()
{
	return MapPtrCollection::Count();
}

bool AnimDataRes::Find(const std::string& key)
{
	return MapPtrCollection::Find(key);
}

AnimData* AnimDataRes::Retrive(const std::string& key)
{
	return MapPtrCollection::Retrive(key);
}
