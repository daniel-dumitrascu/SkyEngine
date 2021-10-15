#include "GameStateManager.h"
#include <algorithm>

int GameStateManager::stackHeadCursor;
GameBaseState* GameStateManager::currentState;
GameBaseState* GameStateManager::stateToDestroy;
GameBaseState* GameStateManager::lastUpdatedState;
std::vector<GameBaseState*>	GameStateManager::statesStack(statesStackSize, nullptr);
bool GameStateManager::resetStack;

void GameStateManager::ReleaseStatesStack()
{
	delete currentState;
	currentState = 0;

	delete stateToDestroy;
	stateToDestroy = 0;

	std::for_each(statesStack.begin(), statesStack.end(), [](GameBaseState* state) { delete state; state = 0; });
}

void GameStateManager::ResetStack()
{
	resetStack = true;
}

void GameStateManager::PushState(GameBaseState* newState, bool saveCurrentStateToStack)
{
	if (currentState)
	{
		if (saveCurrentStateToStack)
		{
			if (statesStack[stackHeadCursor])
			{
				delete statesStack[stackHeadCursor];
				statesStack[stackHeadCursor] = nullptr;
			}

			statesStack[stackHeadCursor] = currentState;

			if (++stackHeadCursor >= statesStackSize)
				stackHeadCursor = 0;
		}
		else
		{
			if (!stateToDestroy)
				stateToDestroy = currentState;
		}

		currentState->SuspendState();
	}

	currentState = newState;
	currentState->ResumeState();
}

void GameStateManager::PopState()
{
	int prevState = ((stackHeadCursor - 1) >= 0) ? stackHeadCursor - 1 : statesStackSize - 1;

	if (statesStack[prevState] && (stateToDestroy == nullptr))
	{
		stateToDestroy = currentState;
		stateToDestroy->SuspendState();

		stackHeadCursor = prevState;
		currentState = statesStack[stackHeadCursor];
		statesStack[stackHeadCursor] = nullptr;

		currentState->ResumeState();
	}
}

void GameStateManager::UpdateCurrentState()
{
	if (currentState)
	{
		lastUpdatedState = currentState;
		currentState->UpdateState();

		if (stateToDestroy)
		{
			delete stateToDestroy;
			stateToDestroy = nullptr;
		}

		if (resetStack)
		{
			while (statesStack[stackHeadCursor])
			{
				delete statesStack[stackHeadCursor];
				statesStack[stackHeadCursor] = nullptr;

				if (--stackHeadCursor < 0)
				{
					stackHeadCursor = statesStackSize - 1;
				}
			}

			stackHeadCursor = 0;
			resetStack = false;
		}
	}
}

void GameStateManager::RenderCurrentState()
{
	if (currentState && currentState == lastUpdatedState)
		currentState->RenderState();
}