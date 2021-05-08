#include "Background.h"
#include "video/Painter.h"
#include "global/GlobalData.h"
#include "GameObjectDefines.h"
#include "utils/UniqueGenerator.h"


Background::Background(WireFrame* mesh, Texture* texture, int shader, const float posX, const float posY, int scale, GameObjectLabel& gameLabel) :
	GameObject(mesh, texture, shader, posX, posY, scale, gameLabel, INPUT_HANDLE_PROFILE_NONE)
{
	Init();
}

Background::~Background()
{
	m_wireframe = NULL;
	m_texture = NULL;
	m_shader_pair_id = 0;
}

std::unique_ptr<GameObject> Background::Clone()
{
	GameObjectLabel newlabel(GAME_OBJECT_ID_BACKGROUND, UniqueGenerator::Instance().GenerateUniqueID());
	return std::make_unique<Background>(m_wireframe,
										m_texture,
										m_shader,
										GetPosition().elem[0],
										GetPosition().elem[1],
										m_scaling,
										newlabel);
}

void Background::Init()
{

}

void Background::PreDraw()
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
}

void Background::Draw()
{
	Painter::DrawData(m_wireframe->GetGeometryCount());
}

void Background::Update()
{

}
