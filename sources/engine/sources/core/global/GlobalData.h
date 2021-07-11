#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include "math/Matrix.h"
#include "time/Time.h"

extern const double FRAMES_PER_SEC;
extern const int SECOND_IN_MILISEC;

extern CoreTime::Timer global_timer;

struct AspectRatio
{
	AspectRatio() : x(0), y(0) { };

	int x;
	int y;
};

struct DisplayResolution
{
	DisplayResolution() : width(0), height(0) { };

	int width;
	int height;
};

extern mat_4x proj_matrix;


// Window aspect ratio
extern const int WINDOWS_ASP_RATIO_X;
extern const int WINDOWS_ASP_RATIO_Y;

// Game aspect ratio
extern const int WORLD_ASP_RATIO_X;
extern const int WORLD_ASP_RATIO_Y;


extern const int WINDOWS_SCREEN_MULTIPLIER;    /* Window multiplier */
extern const int VIRTUAL_WORLD_MULTIPLIER;     /* Game multiplier */


extern const int WORLD_WIDTH_LEFT;
extern const int WORLD_WIDTH_RIGHT;
extern const int WORLD_HEIGHT_UP;
extern const int WORLD_HEIGHT_DOWN;

// Size of game world tile
extern const int WORLD_TILE_WIDTH;
extern const int WORLD_TILE_HEIGHT;

// Total number of tiles on x and y axis
extern const int WORLD_GRID_COLUMN_COUNT;
extern const int WORLD_GRID_ROW_COUNT;

// Movement data
extern const float PLAYER_SPEED_GOAL;
extern const float DELTA_TIME_BOOST;

#endif