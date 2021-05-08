#include "GameStateGameplay.h"
#include "platform/input/InputManager.h"

#if (STRESS_TEST)
	#include "../level/StressLevel.h"
#else
	#include "../level/Level.h"
#endif


GameStateGameplay::GameStateGameplay()
{
	stateID = GAME_STATE_GAMEPLAY;
}

GameStateGameplay::~GameStateGameplay()
{

}

void GameStateGameplay::ResumeState()
{
	Level::GetInstance()->Init();
}

void GameStateGameplay::SuspendState()
{

}

void GameStateGameplay::UpdateState()
{
	Level::GetInstance()->Update();
}

void GameStateGameplay::RenderState()
{
	Level::GetInstance()->Draw();
}