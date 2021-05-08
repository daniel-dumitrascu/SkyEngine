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

void AnimDataRes::Add(AnimData* anim, int key)
{
	MapCollection::Add(anim, key);
}

void AnimDataRes::Remove(const int index)
{
	MapCollection::Remove(index);
}

unsigned int AnimDataRes::Count()
{
	return MapCollection::Count();
}

bool AnimDataRes::Find(const int index)
{
	return MapCollection::Find(index);
}

AnimData* AnimDataRes::Retrive(const int index)
{
	return MapCollection::Retrive(index);
}
