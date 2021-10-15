#pragma once
#include "GameBaseState.h"

#include <memory>
#include <vector>

class GameStateManager
{
public:

	GameStateManager() {};
	~GameStateManager() {};

	static void ReleaseStatesStack();
	static void ResetStack();
	static void PushState(GameBaseState* newState, bool saveCurrentStateToStack = true);
	static void PopState();
	static void UpdateCurrentState();
	static void RenderCurrentState();

private:

	static int stackHeadCursor;
	static const int statesStackSize = 10;
	static std::vector<GameBaseState*> statesStack;
	static GameBaseState* currentState;
	static GameBaseState* stateToDestroy;
	static GameBaseState* lastUpdatedState;
	static bool resetStack;
};