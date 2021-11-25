#include "GameStateGameplay.h"
#include "platform/input/InputManager.h"

#if (STRESS_TEST)
	//TODO - move the stress level to the engine as well
	#include "level/StressLevel.h"
#else
	#include "level/Level.h"
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
	Level::GetInstance()->PreDraw();
	Level::GetInstance()->Draw();
}