#pragma once

#include "game_object/GameObjectLabel.h"
#include "game_object/GameObject.h"
#include "level/LevelData.h"
#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"
#include <memory>

#if(DEBUG_SECTION)
#include "primitive/GameLine.h"
#endif

class StaticObject : public GameObject
{
	public:

		StaticObject(WireFrame* mesh, Texture* texture, int shader, const float posX, const float posY, int scale, GameObjectLabel& gameLabel);
		~StaticObject();
		
		StaticObject(const StaticObject& copy) = delete;
		StaticObject& operator = (const StaticObject& copy) = delete;

		std::unique_ptr<GameObject> Clone() override;

		void Draw();
		void PreDraw();
		void Update();

	private:

		void Init();

#if(DEBUG_SECTION)
		GameLine* leftOutline = nullptr;
		GameLine* rightOutline = nullptr;
		GameLine* topOutline = nullptr;
		GameLine* bottomOutline = nullptr;
#endif
};