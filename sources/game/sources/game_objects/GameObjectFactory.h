#pragma once

#include "utils/UniqueGenerator.h"
#include "game_object/GameObject.h"
#include "level/LevelData.h"
#include "geometry/mesh/MeshLoader.h"
#include "geometry/mesh/MeshResources.h"
#include "animation/AnimDataLoader.h"
#include "animation/AnimDataResources.h"
#include "texture/TextureLoader.h"
#include "texture/TextureResources.h"
#include "shaders/ShaderLoader.h"
#include "shaders/ShaderResources.h"

class GameObjectFactory
{
	public:

		static GameObjectFactory* GetInstance();

		/*
		 * This is going to be used when parsing a level data file
		 */
		GameObject* CreateGameObject(GameObjectPackage& packer);

		/*
		 * These methods are used when creating individual game objects
		 */
		GameObject* CreateGameLine(vec_2x& startPoint, vec_2x& endPoint, int thickness, vec_4x& color);
		GameObject* CreateGameRectangle(vec_2x& pointTopLeft, vec_2x& pointBottomRight, float posX, float posY, vec_4x& color);
		GameObject* CreateGameRectangle(Rectangle& rect, float posX, float posY, vec_4x& color);

	private:

		GameObjectFactory() {};
		GameObjectFactory(const GameObjectFactory& copy) {};
		~GameObjectFactory() {};

		WireFrame* GetTile(GameObjectPackage& pack);
		Texture* GetTexture(GameObjectPackage& pack);
		AnimData* GetAnimation(GameObjectPackage& pack);
		int GetProgram(GameObjectPackage& pack);
};