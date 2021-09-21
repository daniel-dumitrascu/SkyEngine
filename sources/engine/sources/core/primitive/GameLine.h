#pragma once
#include "../game_object/GameObject.h"
#include "Line.h"
#include <memory>

class GameLine : public GameObject
{
	public:
		GameLine(Line& line, const std::string& id);
		GameLine(Line& line, const vec_4x& color, const std::string& id);
		~GameLine();

		std::unique_ptr<GameObject> Clone() override;

		void SetColor(const vec_4x& color);
		const vec_4x& GetColor() { return m_color; }

		void UpdateStartAndEnd(vec_2x& startPoint, vec_2x& endPoint);
		void UpdateStartAndEnd(Line& line);

		void Draw();
		void PreDraw();
		void Update();

	private:
		void Init();

	private:
		Line	m_line;
		vec_4x	m_color;
};