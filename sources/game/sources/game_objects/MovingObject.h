#pragma once
#include "game_object/GameObject.h"

class WireFrame;
class Texture;
class GameObjectLabel;

class MovingObject : public GameObject
{
public:

	MovingObject(WireFrame* mesh, Texture* texture, int shader, const float postX, const float postY, int scale, GameObjectLabel& gameLabel);
	~MovingObject();

	void Draw();
	void PreDraw();
	void Update();

private:

	void Init();

	float m_speed;
};