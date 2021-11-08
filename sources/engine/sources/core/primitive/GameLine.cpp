#include "GameLine.h"
#include "video/Painter.h"
#include "shaders/ShaderDefines.h"
#include "keys/ResourceKeyCollection.h"
#include "shaders/ShaderResources.h"
#include "shaders/ShaderLoader.h"
#include "global/GlobalPaths.h"
#include "../global/GlobalData.h"
#include "utils/UniqueGenerator.h"
#include "camera/Camera.h"
#include "level/Level.h"


GameLine::GameLine(Line& line, const std::string& id):
	GameObject(nullptr, nullptr, -1, 0.0f, 0.0f, 1, id, INPUT_HANDLE_PROFILE_NONE),
	m_line(line)
{
	m_wireframe = m_line.GetConstructedWireFrame();

	// A "GameLine" doesn't have a texture or a fix XY position
	// For position it has start and end points
	Init();
}

GameLine::GameLine(Line& line, const vec_4x& color, const std::string& id) :
	GameObject(nullptr, nullptr, -1, 0.0f, 0.0f, 1, id, INPUT_HANDLE_PROFILE_NONE),
	m_line(line)
{
	m_wireframe = m_line.GetConstructedWireFrame();

	// A "GameLine" doesn't have a texture or a fix XY position
	// For position it has start and end points
	Init();
	SetColor(color);
}

GameLine::~GameLine()
{
	Painter::RemoveGeometryFromGPU(m_wireframe);
	delete m_wireframe;
}

std::unique_ptr<GameObject> GameLine::Clone()
{
	return std::make_unique<GameLine>(m_line, UniqueGenerator::Instance().GenerateUniqueID());
}

void GameLine::Init()
{
	// Construct a world-view-projection matrix 
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);

	// Select the key for the right shader
	ResourceKeyCollection* resourceKeyCollection = ResourceKeyCollection::GetInstance();

	// Do we have this resource loaded?
	// If not, we need to load it
	m_shader = ShaderRes::GetInstance()->RetriveProgramID(SHADER_ID_PRIMITIVE);
	if (!m_shader)
	{
		ShaderRes::GetInstance()->AddShaderPair((ShaderPair*)ShaderLoader::GetInstance()->Load(shaders_path + resourceKeyCollection->GetNameByKey(KEY_SHADER, SHADER_ID_PRIMITIVE)),
			SHADER_ID_PRIMITIVE);

		m_shader = ShaderRes::GetInstance()->RetriveProgramID(SHADER_ID_PRIMITIVE);
	}

	Painter::SendGeometryToGPU(m_wireframe);
	Painter::EnableMeshLocation(Painter::GetInstance()->GetMeshLocation());
}

void GameLine::PreDraw()
{
	Painter::GetInstance()->SelectShader(m_shader);
}

void GameLine::Draw()
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

void GameLine::Update()
{
	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-view-projection matrix */
	//TODO as an optimization I should be able to calculate BuildWorldViewProjMatrix just when the object changed his pos, rotation or scaling
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);
}

void GameLine::SetColor(const vec_4x& color)
{
	vector::vector_4x::SetVector(m_color, color.elem[0], color.elem[1], color.elem[2], color.elem[3]);
}

void GameLine::SetPosition(vec_2x& startPoint, vec_2x& endPoint)
{
	Line line(startPoint, endPoint, m_line.GetThickness());
	m_line = line;

	Painter::RemoveGeometryFromGPU(m_wireframe);
	delete m_wireframe;
	m_wireframe = m_line.GetConstructedWireFrame();

	// A "GameLine" doesn't have a texture or a fix XY position
	// For position it has start and end points
	Init();
}