#include "StaticObject.h"
#include "video/Painter.h"
#include "utils/UniqueGenerator.h"
#include "global/GlobalData.h"
#include "texture/Texture.h"
#include "level/Level.h"


StaticObject::StaticObject(WireFrame* mesh, Texture* texture, int shader, const float posX, const float posY, int scale) :
	GameObject(mesh, texture, shader, posX, posY, scale, INPUT_HANDLE_PROFILE_NONE)
{
	Init();
}

StaticObject::~StaticObject()
{
	Painter::RemoveGeometryFromGPU(m_wireframe);
	m_wireframe = nullptr;
	m_texture = nullptr;

#if(DEBUG_SECTION)
	delete leftOutline;
	delete rightOutline;
	delete topOutline;
	delete bottomOutline;
#endif
}

std::unique_ptr<GameObject> StaticObject::Clone()
{
	return std::make_unique<StaticObject>(m_wireframe,
											m_texture,
											m_shader,
											GetPosition().elem[0],
											GetPosition().elem[1],
											m_scaling);
}

void StaticObject::Init()
{
	Painter::SendGeometryToGPU(m_wireframe);

	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-view-projection matrix */
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);
}

void StaticObject::PreDraw()
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

	/* Select data buffers */
	Painter::SelectArrayBuffer(m_wireframe->GetVBOVert());
	Painter::SelectIndxBuffer(m_wireframe->GetVBOIndx());

	/* Set from where to start the drawing */
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);
	Painter::SetStartDrawData(Painter::GetInstance()->GetTexLocation(), sizeof(Vertex), sizeof(vec_2x));

	/* Set matrix drawing data */
	Painter::SetDrawMatrix4Data(Painter::GetInstance()->GetMemoryLocation(), (const float*)&(m_wp_matrix.elem[0]));
}

void StaticObject::Draw()
{
	Painter::DrawData(m_wireframe->GetGeometryCount());

	// We are going to draw here the debug rect if that's enabled
#if(DEBUG_SECTION)
	if (isOutlineEnabled)
	{
		leftOutline->PreDraw();
		leftOutline->Draw();

		rightOutline->PreDraw();
		rightOutline->Draw();

		topOutline->PreDraw();
		topOutline->Draw();

		bottomOutline->PreDraw();
		bottomOutline->Draw();
	}
#endif
}

void StaticObject::Update()
{
	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-view-projection matrix */
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);

#if(DEBUG_SECTION)
	if (isOutlineEnabled)
	{
		vec_2x newStartPoint;
		vec_2x newEndPoint;
		Rectangle rect = GetObjectWorldRect();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetLeft(), rect.GetBottom());
		GameLine* left = static_cast<GameLine*>(leftOutline);
		left->SetPosition(newStartPoint, newEndPoint);
		left->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetRight(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetBottom());
		GameLine* right = static_cast<GameLine*>(rightOutline);
		right->SetPosition(newStartPoint, newEndPoint);
		right->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetTop());
		GameLine* top = static_cast<GameLine*>(topOutline);
		top->SetPosition(newStartPoint, newEndPoint);
		top->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetBottom());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetBottom());
		GameLine* bottom = static_cast<GameLine*>(bottomOutline);
		bottom->SetPosition(newStartPoint, newEndPoint);
		bottom->Update();
	}
#endif
}
