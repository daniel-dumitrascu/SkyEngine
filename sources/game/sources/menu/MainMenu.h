#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"
#include "input/Controllable.h"

class MainMenu : public Controllable
{
	public:

		MainMenu(WireFrame* mesh, Texture* texture, int shader);
		MainMenu(const MainMenu& copy);
		~MainMenu();

		MainMenu& operator = (const MainMenu& copy);

		void Init();
		void Draw();
		void PreDraw();
		void Update();

		void InputActionNotify(const InputEventBatch& inputBatch);

	private:

		WireFrame* m_mesh;
		Texture* m_texture;
		int m_shader;

		unsigned int m_shader_pair_id;
};

#endif