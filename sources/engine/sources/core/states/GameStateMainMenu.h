#ifndef GAME_STATE_MAIN_MENU_H
#define GAME_STATE_MAIN_MENU_H

#include "GameBaseState.h"
#include "menu/MainMenu.h"
#include <memory>

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

		std::unique_ptr<MainMenu> m_main_menu;
};


#endif