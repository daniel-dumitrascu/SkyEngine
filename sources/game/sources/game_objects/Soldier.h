#ifndef SOLDIER_H
#define SOLDIER_H

#include "game_object/GameObjectLabel.h"
#include "game_object/GameObject.h"
#include "level/LevelData.h"
#include "texture/Texture.h"
#include "animation/player/AnimPlayer.h"
#include "actions/Actions.h"
#include <memory>


class SoldierObject : public GameObject
{

	enum SoldierState
	{
		as_soldier_idle = 0,
		as_soldier_sword_on = 1,
		as_soldier_sword_off = 2,
		as_soldier_attack = 3,
		as_soldier_die = 4,
		as_soldier_die_sword = 5,
		as_soldier_climb = 6,
		as_soldier_walk = 7,
		as_soldier_walk_sword = 8,
		as_soldier_run_sword_off = 9,
		as_soldier_run_sword_on = 10
	};

	public:

		SoldierObject(Texture* tex, int shader, const float posX, const float posY, int scale, GameObjectLabel& gameLabel);
		~SoldierObject();

		SoldierObject(const SoldierObject& copy) = delete;
		SoldierObject& operator = (const SoldierObject& copy) = delete;
		
		std::unique_ptr<GameObject> Clone() override;

		void Draw();
		void PreDraw();
		void Update();

		void InputActionNotify(const InputEventBatch& inputBatch);

	private:
		
		void Init();

		void OnMoveLeft();
		void OnMoveRight();
		void OnMoveUp();
		void OnMoveDown();
		void OnRotateLeft() {};
		void OnRotateRight() {};
		void OnAttack();
		void OnDefense() {};

	private:

		//TODO maybe I can move the AnimPlayer in the Entity class
		AnimPlayer* m_anim_player;

		void (SoldierObject::*m_action_handler[Actions::Gameplay::GAMEPLAY_COUNT])();
};


#endif