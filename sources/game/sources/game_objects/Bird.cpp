#include "Bird.h"
#include "global/GlobalData.h"
#include "video/Painter.h"
#include "time/Time.h"
#include "animation/AnimDataResources.h"
#include "entities/GameObjectDefines.h"
#include "defines/ResourceDefines.h"
#include "utils/UniqueGenerator.h"

static int anim_index = 0;


BirdObject::BirdObject(Texture* tex, 
					   int shader, 
					   const float posX, 
					   const float posY, 
					   int scale) : GameObject(NULL,
												tex, 
												shader, 
												posX,
												posY,
												scale,
												INPUT_HANDLE_PROFILE_GAMEOBJECT)
{	
	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::BuildWorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);

	Init();
}

BirdObject::~BirdObject()
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

std::unique_ptr<GameObject> BirdObject::Clone()
{
	return std::make_unique<BirdObject>(m_texture,
										m_shader,
										GetPosition().elem[0],
										GetPosition().elem[1],
										m_scaling);
}

void BirdObject::Init()
{
	AnimData* anim_data = AnimDataRes::GetInstance()->Retrive(RESOURCE_ANIMATION_ID_BIRD);
	m_anim_player = new AnimPlayer(anim_data);

	/* Starting the animation */
	m_anim_player->SetState(0);
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

void BirdObject::PreDraw()
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

	Painter::EnableMeshLocation(Painter::GetInstance()->GetMeshLocation());
	Painter::EnableTextureLocation(Painter::GetInstance()->GetTexLocation());
	/***********************************************************************************************************************/

	/* Texture binding */
	Painter::SetBindTexture(m_texture->bind_id);

	/* Set matrix drawing data */
	Painter::SetDrawMatrix4Data(Painter::GetInstance()->GetMemoryLocation(), (const float*)&(m_wp_matrix.elem[0]));

	/* Select buffers */
	Painter::SelectArrayBuffer(m_anim_player->GetCurrentFrame()->GetVBOVert());
	Painter::SelectIndxBuffer(m_anim_player->GetCurrentFrame()->GetVBOIndx());
	
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);
	Painter::SetStartDrawData(Painter::GetInstance()->GetTexLocation(), sizeof(Vertex), sizeof(vec_2x));
}

void BirdObject::Draw()
{	
	Painter::DrawData(m_anim_player->GetCurrentFrame()->GetGeometryCount());
}

void BirdObject::Update()
{
	/* Animation update phase */
	m_anim_player->PlayAnim();

	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::BuildWorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);
}