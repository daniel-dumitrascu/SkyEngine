#pragma once

enum GameObjectID
{
	GAME_OBJECT_ID_UNDEFINED     = 0,
	GAME_OBJECT_ID_PLAYER        = 1,
	GAME_OBJECT_ID_STATIC_BLOCK  = 2,
	GAME_OBJECT_ID_BIRD          = 3,
	GAME_OBJECT_ID_SOLDIER       = 4,
	GAME_OBJECT_ID_BACKGROUND    = 5,
	GAME_OBJECT_ID_GRASS         = 7,
	GAME_OBJECT_ID_MOVING_OBJECT = 8,

	// These 2 are defined in engine
	GAME_OBJECT_ID_LINE			 = 9,
	GAME_OBJECT_ID_RECT			 = 10
};