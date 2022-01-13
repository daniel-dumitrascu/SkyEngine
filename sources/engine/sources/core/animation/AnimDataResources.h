#ifndef ANIM_RESOURCES_H
#define ANIM_RESOURCES_H

#include "utils/MapCollection.h"
#include "AnimData.h"

class AnimDataRes : private MapPtrCollection<AnimData>
{
	public:

		static AnimDataRes* GetInstance();

		void Add(const std::string& key, const std::string pathToResource);
		void Remove(const std::string& key);
		unsigned int Count();
		bool Find(const std::string& key);
		AnimData* Retrive(const std::string& key);

	private:

		AnimDataRes() {};
		AnimDataRes(const AnimDataRes& copy) {};
		~AnimDataRes() {};

		AnimDataRes& operator=(const AnimDataRes& copy);
};

#endif