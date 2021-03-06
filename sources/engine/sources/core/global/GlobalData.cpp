#include "GlobalData.h"

const double FRAMES_PER_SEC = 60.0;
int const SECOND_IN_MILISEC = 1000;

CoreTime::Timer global_timer((float)SECOND_IN_MILISEC / FRAMES_PER_SEC);

mat_4x proj_matrix;

// The screen resolution is calculated as following: 
// (Window aspect ratio) * (Window multiplier)

// Window aspect ratio
const int WINDOWS_ASP_RATIO_X = 16;
const int WINDOWS_ASP_RATIO_Y = 9;

// Window multiplier
const int WINDOWS_SCREEN_MULTIPLIER = 100;

// Game world details
const int WORLD_GRID_WIDTH_COUNT = 16;
const int WORLD_GRID_HEIGHT_COUNT = 16;

const int GRID_SECTOR_WIDTH = 400;
const int GRID_SECTOR_HEIGHT = 400;

const int WORLD_WIDTH = WORLD_GRID_WIDTH_COUNT * GRID_SECTOR_WIDTH;
const int WORLD_HEIGHT = WORLD_GRID_HEIGHT_COUNT * GRID_SECTOR_HEIGHT;

// Movement data
const float PLAYER_SPEED_GOAL = 700.0f;
const float DELTA_TIME_BOOST = 2000.0f;