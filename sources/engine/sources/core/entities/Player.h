#pragma once
#include "entities/GameObject.h"
#include "actions/Actions.h"

#if(DEBUG_SECTION)
#include "primitive/GameLine.h"
#endif

class Player : public GameObject
{

public:

	Player(WireFrame* mesh, Texture* texture, int shader, const float postX, const float postY, int scale, float zBuffer);
	~Player();

	void Draw();
	void PreDraw();
	void Update();

	void InputActionNotify(const InputEventBatch& inputBatch);

private:

	Player(const Player& copy) = delete;
	Player& operator = (const Player& copy) = delete;

	void Init();
	void Move();

	void OnMovement(void* extraData);

	void OnRotateLeft() {};
	void OnRotateRight() {};
	void OnAttack() {};
	void OnDefense() {};

	void ComputeDirection(const vec_3x* newOrientation);
	void UpdateMovement(float framesElapsedTime);

private:

	vec_3x currDirection;
	vec_3x newDirection;
	vec_3x lastFramePos;

	float speedGoal;
	float currentSpeed;

	bool hasObjectMovedThisFrame;

	void (Player::*m_action_handler[Actions::Gameplay::GAMEPLAY_COUNT])(void* extraData);
};