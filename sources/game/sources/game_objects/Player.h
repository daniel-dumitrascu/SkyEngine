#ifndef PLAYER_H
#define PLAYER_H

#include "game_object/GameObjectLabel.h"
#include "game_object/GameObject.h"
#include "level/LevelData.h"
#include "actions/Actions.h"
#include "input/Controllable.h"
#include "math/Vector.h"

#if(DEBUG_SECTION)
#include "primitive/GameLine.h"
#endif


class WireFrame;
struct Texture;


class Player : public GameObject
{

	public:

		Player(WireFrame* mesh, Texture* texture, int shader, const float postX, const float postY, int scale, GameObjectLabel& gameLabel);
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

		void OnMoveUp();
		void OnMoveDown();
		void OnMoveLeft();
		void OnMoveRight();

		void OnRotateLeft() {};
		void OnRotateRight() {};
		void OnAttack() {};
		void OnDefense() {};

		void ComputeDirection(float x, float y, float z);

	private:

		vec_3x currDirection;
		vec_3x newDirection;
		vec_3x lastFramePos;

		float speedGoal;
		float currentSpeed;

		bool hasObjectMovedThisFrame;

		void (Player::*m_action_handler[Actions::Gameplay::GAMEPLAY_COUNT])();

#if(DEBUG_SECTION)
		GameLine* leftOutline = nullptr;
		GameLine* rightOutline = nullptr;
		GameLine* topOutline = nullptr;
		GameLine* bottomOutline = nullptr;
#endif
};

#endif