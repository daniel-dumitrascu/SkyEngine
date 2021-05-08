#ifndef GAME_STATE_MAIN_MENU_H
#define GAME_STATE_MAIN_MENU_H

#include "GameBaseState.h"
#include "../menu/MainMenu.h"

class GameStateMainMenu : public GameBaseState
{
	public:

		GameStateMainMenu();
		~GameStateMainMenu();

	protected:

		void ResumeState();
		void SuspendState();
		void UpdateState();
		void RenderState();

	private:

		void UnsubscribeFromInput();

	private:

		MainMenu* m_main_menu;
};


#endif