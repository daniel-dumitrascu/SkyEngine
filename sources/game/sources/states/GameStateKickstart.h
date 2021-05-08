#ifndef GAME_STATE_KICKSTART_H
#define GAME_STATE_KICKSTART_H

#include "GameBaseState.h"
#include "time/Time.h"
#include "../splash/SplashScreen.h"

class GameStateKickstart : public GameBaseState
{
	public:

		GameStateKickstart();
		~GameStateKickstart();

	protected:

		void ResumeState();
		void SuspendState();
		void UpdateState();
		void RenderState();

	private:

		bool is_done_loading;
		SplashScreen* m_splash_screen;
		CoreTime::Timer m_splash_timer;
};

#endif