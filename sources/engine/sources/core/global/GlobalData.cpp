#include "GlobalData.h"

const double FRAMES_PER_SEC = 60.0;
int const SECOND_IN_MILISEC = 1000;

CoreTime::Timer global_timer((float)SECOND_IN_MILISEC / FRAMES_PER_SEC);

mat_4x proj_matrix;


/* Note 1: For best quality game world aspect ratio MUST be the same as the windows aspect ratio */
/* Note 2: When you want to change the resolution, first change the aspect ratio for the window and world and */
/*         then change the multiplayer (WINDOWS_SCREEN_MULTIPLIER) value till you reach the wanted resolution */

/* Window aspect ratio */
const int WINDOWS_ASP_RATIO_X = 16;
const int WINDOWS_ASP_RATIO_Y = 9;

/* Game aspect ratio */
const int WORLD_ASP_RATIO_X = 16;
const int WORLD_ASP_RATIO_Y = 9;


const int WINDOWS_SCREEN_MULTIPLIER = 60;   /* Window multiplier */
const int VIRTUAL_WORLD_MULTIPLIER = 100;   /* Game multiplier */


const int WORLD_WIDTH_LEFT = 0.0f;
const int WORLD_WIDTH_RIGHT = WORLD_ASP_RATIO_X * VIRTUAL_WORLD_MULTIPLIER;
const int WORLD_HEIGHT_UP = 0.0f;
const int WORLD_HEIGHT_DOWN = WORLD_ASP_RATIO_Y * VIRTUAL_WORLD_MULTIPLIER;

/* Size of game world tile in pixels */
const int WORLD_TILE_WIDTH = 100;
const int WORLD_TILE_HEIGHT = 100;

/* Total number of tiles on x and y axis */
const int WORLD_GRID_COLUMN_COUNT = WORLD_WIDTH_RIGHT / WORLD_TILE_WIDTH;
const int WORLD_GRID_ROW_COUNT = WORLD_HEIGHT_DOWN / WORLD_TILE_HEIGHT;

// Movement data
const float PLAYER_SPEED_GOAL = 600.0f;
const float DELTA_TIME_BOOST = 2000.0f;