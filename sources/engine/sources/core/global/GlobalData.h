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

// Window multiplier
extern const int WINDOWS_SCREEN_MULTIPLIER;

// Game world details
extern const int WORLD_GRID_WIDTH_COUNT;
extern const int WORLD_GRID_HEIGHT_COUNT;

extern const int GRID_SECTOR_WIDTH;
extern const int GRID_SECTOR_HEIGHT;

extern const int WORLD_WIDTH;
extern const int WORLD_HEIGHT;

// Movement data
extern const float PLAYER_SPEED_GOAL;
extern const float DELTA_TIME_BOOST;

#endif