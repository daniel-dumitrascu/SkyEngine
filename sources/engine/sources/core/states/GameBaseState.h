#pragma once
#include "StateID.h"

class GameBaseState
{
	public:

		GameBaseState() : stateID(GAME_STATE_UNDEFINED) {};
		virtual ~GameBaseState() {};

		virtual void RenderState() = 0;	
		virtual void SuspendState() = 0;
		virtual void ResumeState() = 0;
		virtual void UpdateState() = 0;

	protected:

		StateID	stateID;
};
