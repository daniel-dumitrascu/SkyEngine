#include "MovingObject.h"
#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"
#include "game_object/GameObjectLabel.h"
#include "video/Painter.h"
#include "global/GlobalData.h"


MovingObject::MovingObject(WireFrame* mesh, Texture* texture, int shader, const float postX, const float postY, int scale, GameObjectLabel& gameLabel):
	GameObject(mesh, texture, shader, postX, postY, scale, gameLabel, INPUT_HANDLE_PROFILE_NONE),
	m_speed(20.0f)
{
	Init();
}

MovingObject::~MovingObject()
{
	Painter::RemoveGeometryFromGPU(m_wireframe);
	m_wireframe = NULL;
	m_texture = NULL;
}

void MovingObject::Draw()
{
	/* Draw the actual data */
	Painter::DrawData(m_wireframe->GetGeometryCount());
}

void MovingObject::PreDraw()
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

	/* Selecting the texture */
	Painter::SetBindTexture(m_texture->bind_id);

	/* Select data buffers */
	Painter::SelectArrayBuffer(m_wireframe->GetVBOVert());
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);

	Painter::SelectIndxBuffer(m_wireframe->GetVBOIndx());
	Painter::SetStartDrawData(Painter::GetInstance()->GetTexLocation(), sizeof(Vertex), sizeof(vec_2x));

	/* Set matrix drawing data */
	Painter::SetDrawMatrix4Data(Painter::GetInstance()->GetMemoryLocation(), (const float*)&(m_wp_matrix.elem[0]));
}

void MovingObject::Update()
{
	// TODO - For the purpose of having a moving object I will place the moving logic here.
	// But, this is not correct, the object should not know about this logic, this should be external, in an AI
	if(m_world_position.elem[0] < ((WORLD_ASP_RATIO_X * VIRTUAL_WORLD_MULTIPLIER) - 100))
		m_world_position.elem[0] += 1.0f;
	
	matrix::game_matrix::SetWorldPosition(m_world_matrix, m_world_position);

	//Warning - setting the flag ON and OFF for OBJECT_IS_MOVING must be made in the object. 
	//In the Level class I only check if the current object is still moving but I don't take any decisions on setting this flag OFF.
	SetFlagON(OBJECT_IS_MOVING);


	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::WorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);
}

void MovingObject::Init()
{
	Painter::SendGeometryToGPU(m_wireframe);

	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::WorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);
}