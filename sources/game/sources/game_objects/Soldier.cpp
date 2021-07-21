#include "Soldier.h"
#include "global/GlobalData.h"
#include "video/Painter.h"
#include "time/Time.h"
#include "platform/input/InputManager.h"
#include "../states/GameStateManager.h"
#include "../states/GameStateMainMenu.h"
#include "animation/AnimDataResources.h"
#include "GameObjectDefines.h"
#include "../defines/ResourceDefines.h"
#include "utils/UniqueGenerator.h"
#include "bindings/BindingsManager.h"


static int anim_index = 0;


SoldierObject::SoldierObject(Texture* tex, 
							int shader, 
							const float posX, 
							const float posY, 
							int scale, 
							GameObjectLabel& gameLabel) :
		GameObject(NULL, 
					tex, 
					shader, 
					posX, 
					posY, 
					scale, 
					gameLabel,
					INPUT_HANDLE_PROFILE_GAMEOBJECT)
{
	SetFlagOFF(OBJECT_IS_CONTROLLABLE);

	m_action_handler[Actions::Gameplay::GAMEPLAY_UNDEFINED] = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_UP] = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_DOWN] = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_LEFT] = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_RIGHT] = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_ATTACK] = &SoldierObject::OnAttack;

	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::WorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);

	Init();
}

SoldierObject::~SoldierObject()
{
	int index = 0;
	int start, end;
	AnimData* anim_data = m_anim_player->GetAnimData();

	while (anim_data->GetStateLimit(index, &start, &end))
	{
		for (int i = start; i <= end; ++i)
			Painter::RemoveGeometryFromGPU(anim_data->GetFrame(i));

		++index;
	}

	delete m_anim_player;
	m_texture = NULL;
}

std::unique_ptr<GameObject> SoldierObject::Clone()
{
	GameObjectLabel newlabel(GAME_OBJECT_ID_SOLDIER, UniqueGenerator::Instance().GenerateUniqueID());
	return std::make_unique<SoldierObject>(m_texture,
											m_shader,
											GetPosition().elem[0],
											GetPosition().elem[1],
											m_scaling,
											newlabel);
}

void SoldierObject::Init()
{
	AnimData* anim_data = AnimDataRes::GetInstance()->Retrive(RESOURCE_ANIMATION_ID_SOLDIER);
	m_anim_player = new AnimPlayer(anim_data);

	/* Starting the animation */
	m_anim_player->SetState(as_soldier_idle);
	m_anim_player->ResumeAnim();

	//TODO refactor
	/* Send animation data to GPU */
	int index = 0;
	int start, end;

	while (anim_data->GetStateLimit(index, &start, &end))
	{
		for (int i = start; i <= end; ++i)
			Painter::SendGeometryToGPU(anim_data->GetFrame(i));

		++index;
	}
}

void SoldierObject::PreDraw()
{
	//TODO function calls that must be executed in the init step
	/***********************************************************************************************************************/
	// move them in DrawScheme
	// for every shader pair :)
	// I call them once in init and then send the info as mesh_id and tex_id to every object in the scene

	//TODO call them each time I need to draw objects 
	//the functions will be called to every object group from the scenne that is assigned to a shader pair
	Painter::GetInstance()->SelectShader(m_shader);
	Painter::SetActiveTexture(m_shader, "s_texture");
	/***********************************************************************************************************************/

	/* Texture binding */
	Painter::SetBindTexture(m_texture->bind_id);

	/* Set matrix drawing data */
	Painter::SetDrawMatrix4Data(Painter::GetInstance()->GetMemoryLocation(), (const float*)&(m_wp_matrix.elem[0]));

	/* Select buffers */
	Painter::SelectArrayBuffer(m_anim_player->GetCurrentFrame()->GetVBOVert());
	Painter::SelectIndxBuffer(m_anim_player->GetCurrentFrame()->GetVBOIndx());

	/* Set from where to start the drawing */
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);
	Painter::SetStartDrawData(Painter::GetInstance()->GetTexLocation(), sizeof(Vertex), sizeof(vec_2x));
}

void SoldierObject::Draw()
{
	Painter::DrawData(m_anim_player->GetCurrentFrame()->GetGeometryCount());
}

void SoldierObject::Update()
{
	/* Animation update phase */
	if (m_anim_player->PlayAnim() == false)
	{
		m_anim_player->SuspendAnim();
		m_anim_player->SetState(as_soldier_idle);
		m_anim_player->ResumeAnim();
	}
		
	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::WorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);
}

void SoldierObject::OnAttack()
{
	/* Change animation to attack */
	//m_anim_player->SuspendAnim();
	m_anim_player->SetState(as_soldier_attack);
	m_anim_player->ResumeAnim();
}