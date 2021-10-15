#ifndef STRESS_LEVEL_GAME
#define STRESS_LEVEL_GAME

#if 0
#include "geometry/baching/DrawScheme.h"

#include "../game_objects/Player.h"
#include "../game_objects/Bird.h"
#include "../game_objects/StaticObject.h"


class StressLevel : public DrawScheme
{
	public:

		StressLevel();
		StressLevel(const StressLevel& copy);
		~StressLevel();

		void Init();
		void Update();
		void Draw();

	private:

		int maxim = 10;
		BirdObject**  bird;
};
#endif

#endif