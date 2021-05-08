#pragma once
#include "../game_object/GameObject.h"
#include "Rectangle.h"
#include <memory>

class GameRectangle : public GameObject
{
	public:
		GameRectangle(Rectangle& rect, float posX, float posY, GameObjectLabel& gameLabel);
		GameRectangle(Rectangle& rect, float posX, float posY, const vec_4x& color, GameObjectLabel& gameLabel);
		~GameRectangle();

		std::unique_ptr<GameObject> Clone() override;

		void SetColor(const vec_4x& color);
		const vec_4x& GetColor() { return m_color; }

		void Draw();
		void PreDraw();
		void Update();

	private:
		void Init();

	private:
		vec_4x	m_color;
};