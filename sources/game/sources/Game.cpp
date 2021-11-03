#include "Game.h"
#include "platform/Platform.h"
#include "video/Painter.h"
#include "platform/input/DeviceDefinitions.h"
#include "global/GlobalData.h"
#include "states/GameStateManager.h"
#include "states/GameStateKickstart.h"
#include <time.h>      


Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

Game::Game()
{

}

Game::~Game()
{
	GameStateManager::ReleaseStatesStack();
}

void Game::Init()
{
	srand(time(NULL));

	/* Set the identity for projection matrix */
	matrix::matrix_4x::SetIdentity(proj_matrix);

	/* Build a 2D projection matrix */
	matrix::game_matrix::BuildProjectionMatrix(proj_matrix, 
												0.0f, 
												(float)(WINDOWS_ASP_RATIO_X * WINDOWS_SCREEN_MULTIPLIER), 
												0.0f, 
												(float)(WINDOWS_ASP_RATIO_Y * WINDOWS_SCREEN_MULTIPLIER), 
												1.0f, 
												-1.0f);

	GameStateManager::PushState(new GameStateKickstart);
	is_running = true;
}

void Game::Update()
{	
	GameStateManager::UpdateCurrentState();
}

void Game::Draw()
{
	GameStateManager::RenderCurrentState();
}