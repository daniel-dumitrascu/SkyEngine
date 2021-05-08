#ifndef GAME_H
#define GAME_H

#include "../../engine/sources/application/Application.h"


class Game : public Application
{
	public:

		static Game& GetInstance();

		Game(const Game& copy) = delete;
		Game& operator=(const Game& copy) = delete;		
		
		void Init();
		void Update();
		void PreDraw();
		void Draw();
		void Close() {};

	private:

		Game();
		~Game();
};

#endif