#include "SplashScreen.h"
#include "video/Painter.h"
#include "global/GlobalData.h"


SplashScreen::SplashScreen(WireFrame* mesh, Texture* texture, int shader) : m_mesh(mesh),
																			m_texture(texture),
																			m_shader(shader)
{

}

SplashScreen::SplashScreen(const SplashScreen& copy) : m_mesh(copy.m_mesh),
													   m_texture(copy.m_texture)
{

}

SplashScreen::~SplashScreen()
{
	Painter::RemoveGeometryFromGPU(m_mesh);
	m_mesh = NULL;
	m_texture = NULL;
	m_shader_pair_id = 0;
}

SplashScreen& SplashScreen::operator = (const SplashScreen& copy)
{
	/*TODO - TO DO*/
	return *this;
}

void SplashScreen::Init()
{
	/*TODO This calls must be done only once in init*/
	Painter::SendGeometryToGPU(m_mesh);
}

void SplashScreen::Draw()
{
	Painter::DrawData(m_mesh->GetGeometryCount());
}

void SplashScreen::PreDraw()
{
	/* Texture binding */
	Painter::SetBindTexture(m_texture->bind_id);

	/* Select data buffers */
	Painter::SelectArrayBuffer(m_mesh->GetVBOVert());
	Painter::SelectIndxBuffer(m_mesh->GetVBOIndx());

	/* Set from where to start the drawing */
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);
	Painter::SetStartDrawData(Painter::GetInstance()->GetTexLocation(), sizeof(Vertex), sizeof(vec_2x));
}

void SplashScreen::Update()
{

}
