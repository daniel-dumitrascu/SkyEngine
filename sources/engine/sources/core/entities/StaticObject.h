#pragma once

#include "entities/GameObject.h"

#if(DEBUG_SECTION)
#include "primitive/GameLine.h"
#endif

class StaticObject : public GameObject
{
public:

	StaticObject(WireFrame* mesh, Texture* texture, int shader, const float posX, const float posY, int scale, float zBuffer);
	~StaticObject();

	StaticObject(const StaticObject& copy) = delete;
	StaticObject& operator = (const StaticObject& copy) = delete;

	std::unique_ptr<GameObject> Clone() override;

	void Draw();
	void PreDraw();
	void Update();

private:

	void Init();
};