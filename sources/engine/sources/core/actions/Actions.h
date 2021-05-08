#ifndef LOGIC_EVENTS
#define LOGIC_EVENTS

namespace Actions
{
	// Reserved range 0 - 99
	enum Gameplay
	{
		GAMEPLAY_UNDEFINED = 0,
		GAMEPLAY_MOVE_UP,
		GAMEPLAY_MOVE_DOWN,
		GAMEPLAY_MOVE_LEFT,
		GAMEPLAY_MOVE_RIGHT,
		GAMEPLAY_ATTACK,

		GAMEPLAY_COUNT
	};

	// Reserved range 100 - 199
	enum Menu
	{
		MENU_UNDEFINED = 100,
		MENU_CLICK,

		MENU_COUNT = (MENU_CLICK - 100) + 1
	};

	// Reserved range 200 - 299
	enum Game
	{
		GAME_UNDEFINED = 200,
		GAME_EXIT,

		GAME_COUNT = (GAME_EXIT - 200) + 1
	};

	// Reserved range 300 - 399
	enum Debug
	{
		DEBUG_UNDEFINED = 300,
		DEBUG_GRID_DRAW,
		DEBUG_OBJECT_TILE_MAPPING,
		DEBUG_OBJECT_RECTANGLE,

		DEBUG_COUNT = (DEBUG_OBJECT_RECTANGLE - 300) + 1
	};
}

#endif