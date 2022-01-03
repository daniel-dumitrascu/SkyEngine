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
	MapCollection::Add(anim, key);
}

void AnimDataRes::Remove(const std::string& key)
{
	MapCollection::Remove(key);
}

unsigned int AnimDataRes::Count()
{
	return MapCollection::Count();
}

bool AnimDataRes::Find(const std::string& key)
{
	return MapCollection::Find(key);
}

AnimData* AnimDataRes::Retrive(const std::string& key)
{
	return MapCollection::Retrive(key);
}
