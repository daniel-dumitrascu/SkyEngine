#ifndef ANIM_RESOURCES_H
#define ANIM_RESOURCES_H

#include "utils/MapCollection.h"
#include "AnimData.h"

class AnimDataRes : private MapCollection<AnimData*>
{
	public:

		static AnimDataRes* GetInstance();

		void Add(AnimData* mesh, int key);
		void Remove(const int index);
		unsigned int Count();
		bool Find(const int index);
		AnimData* Retrive(const int index);

	private:

		AnimDataRes() {};
		AnimDataRes(const AnimDataRes& copy) {};
		~AnimDataRes() {};

		AnimDataRes& operator=(const AnimDataRes& copy);
};

#endif