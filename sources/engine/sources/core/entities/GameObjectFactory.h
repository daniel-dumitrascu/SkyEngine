#pragma once

#include "entities/GameObject.h"
#include "animation/AnimData.h"
#include "camera/Camera.h"
#include "primitive/GameLine.h"

class GameObjectFactory
{
public:

	static GameObjectFactory* GetInstance();

	/*
	 * This is going to be used when parsing a level data file
	 */
	GameObject* CreateGameObject(GameObjectPackage& packer);
	Camera* CreateCamera(const CameraPackage& cameraPack);

	/*
	 * These methods are used when creating individual game objects
	 */
	GameObject* CreateGameLine(vec_2x& startPoint, vec_2x& endPoint, int thickness, vec_4x& color);
	GameObject* CreateGameRectangle(vec_2x& recLeftTop, vec_2x& recRightBottom, vec_4x& color);

private:

	GameObjectFactory() {};
	GameObjectFactory(const GameObjectFactory& copy) {};
	~GameObjectFactory() {};

	WireFrame* GetMesh(GameObjectPackage& pack);
	Texture* GetTexture(GameObjectPackage& pack);
	AnimData* GetAnimation(GameObjectPackage& pack);
	int GetProgram(GameObjectPackage& pack);

#if(DEBUG_SECTION)
	void ConstructDebugOutlines(GameObject* obj, GameLine **leftOutline, GameLine **rightOutline, GameLine **topOutline, GameLine **bottomOutline);
#endif
};