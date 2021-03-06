#include "GameRectangle.h"
#include "video/Painter.h"
#include "shaders/ShaderResources.h"
#include "shaders/ShaderLoader.h"
#include "global/GlobalPaths.h"
#include "../global/GlobalData.h"
#include "math/Geometry.h"
#include "utils/UniqueGenerator.h"
#include "level/Level.h"


GameRectangle::GameRectangle(const vec_2x& recLeftTop, const vec_2x& recRightBottom, const vec_4x& color) :
	GameObject(nullptr, nullptr, -1, 0.0f, 0.0f, 1, INPUT_HANDLE_PROFILE_NONE)
{
	m_rectangle = std::make_unique<Rectangle>(recLeftTop, recRightBottom);
	m_wireframe = Geometry::ConstrWireframeFromRect(*m_rectangle);

	// Once we have a rect we can now calculate the size of that rect (height and lenght)
	vec_2x rectDimensions = Geometry::CalculateRectDimensions(*m_rectangle);
	m_rectHeight = rectDimensions.elem[0];
	m_rectLenght = rectDimensions.elem[1];

	Init();
	SetColor(color);
}

GameRectangle::~GameRectangle()
{
	Painter::RemoveGeometryFromGPU(m_wireframe);
}

std::unique_ptr<GameObject> GameRectangle::Clone()
{
	return std::make_unique<GameRectangle>(vec_2x(m_rectangle->GetLeft(), m_rectangle->GetTop()), 
										   vec_2x(m_rectangle->GetRight(), m_rectangle->GetBottom()),
										   m_color);
}

void GameRectangle::Init()
{
	// Construct a world-view-projection matrix 
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);

	// Do we have this resource loaded?
	// If not, we need to load it
	std::string primitivePath = "assets/shaders/primitive";
	std::string fullpath = working_dir_path + "/" + primitivePath;
	m_shader = ShaderRes::GetInstance()->Retrive(primitivePath);
	if (!m_shader)
	{
		ShaderRes::GetInstance()->Add(primitivePath, fullpath);
		m_shader = ShaderRes::GetInstance()->Retrive(primitivePath);
	}

	Painter::SendGeometryToGPU(m_wireframe);
	Painter::EnableMeshLocation(Painter::GetInstance()->GetMeshLocation());
}

void GameRectangle::PreDraw()
{
	Painter::GetInstance()->SelectShader(m_shader);
}

void GameRectangle::Draw()
{
	// Select data buffers
	Painter::SelectArrayBuffer(m_wireframe->GetVBOVert());
	Painter::SelectIndxBuffer(m_wireframe->GetVBOIndx());

	// Set from where to start the drawing
	Painter::SetDrawColorData(Painter::GetInstance()->GetColorLocation(), (const float*)&(m_color.elem[0]));

	// Set mesh drawing
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);

	// Set matrix drawing data
	Painter::SetDrawMatrix4Data(Painter::GetInstance()->GetMemoryLocation(), (const float*)&(m_wp_matrix.elem[0]));

	Painter::DrawData(m_wireframe->GetGeometryCount());
}

void GameRectangle::Update()
{
	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-view-projection matrix */
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);
}

void GameRectangle::SetColor(const vec_4x& color)
{
	vector::vector_4x::SetVector(m_color, color.elem[0], color.elem[1], color.elem[2], color.elem[3]);
}