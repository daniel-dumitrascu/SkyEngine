#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"

class SplashScreen
{
	public:

		SplashScreen(WireFrame* mesh, Texture* texture, int shader);
		SplashScreen(const SplashScreen& copy);
		~SplashScreen();

		SplashScreen& operator = (const SplashScreen& copy);

		void Init();
		void Draw();
		void PreDraw();
		void Update();

	private:

		void OnAction_Attack() {};
		void OnAction_Left() {};
		void OnAction_Right() {};
		void OnAction_Up() {};
		void OnAction_Down() {};
		void OnAction_Far() {};
		void OnAction_Near() {};

	private:

		WireFrame* m_mesh;
		Texture* m_texture;
		int m_shader;

		unsigned int m_shader_pair_id;
};

#endif