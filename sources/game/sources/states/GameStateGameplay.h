#ifndef GAME_STATE_GAMEPLAY_H
#define GAME_STATE_GAMEPLAY_H

#include "GameBaseState.h"


class GameStateGameplay : public GameBaseState
{
	public:

		GameStateGameplay();
		~GameStateGameplay();

	protected:

		void ResumeState();
		void SuspendState();
		void UpdateState();
		void RenderState();
};


#endif