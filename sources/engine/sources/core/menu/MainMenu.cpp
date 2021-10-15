#include "MainMenu.h"
#include "video/Painter.h"
#include "global/GlobalData.h"
#include "platform/input/InputManager.h"
#include "platform/input/DeviceDefinitions.h"
#include "actions/Actions.h"
#include "bindings/BindingsManager.h"
#include "states/GameStateManager.h"
#include "states/GameStateGameplay.h"


MainMenu::MainMenu(WireFrame* mesh, Texture* texture, int shader) : Controllable(INPUT_HANDLE_PROFILE_MENU),
																	m_mesh(mesh),
																	m_texture(texture),
																	m_shader(shader)
{

}

MainMenu::MainMenu(const MainMenu& copy) : Controllable(INPUT_HANDLE_PROFILE_MENU),
										   m_mesh(copy.m_mesh),
										   m_texture(copy.m_texture)
{

}

MainMenu::~MainMenu()
{
	m_mesh = NULL;
	m_texture = NULL;
	m_shader_pair_id = 0;
}

MainMenu& MainMenu::operator = (const MainMenu& copy)
{
	/*TODO*/
	return *this;
}

void MainMenu::Init()
{

}

void MainMenu::Draw()
{
	Painter::DrawData(m_mesh->GetGeometryCount());
}

void MainMenu::PreDraw()
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

void MainMenu::Update()
{

}

void MainMenu::InputActionNotify(const InputEventBatch& inputBatch)
{
	int const batchSize = inputBatch.getDataBatchSize();
	if(batchSize > 0)
	{
		for(int i=0; i < batchSize; ++i)
		{
			const DataBindingWrapper* wrapper = inputToActionBindings->GetBinding(inputBatch.getDataAtIndex(i));

			if(wrapper == nullptr)
				continue;

			if (wrapper->action == Actions::Menu::MENU_CLICK)
				GameStateManager::PushState(new GameStateGameplay);
			else if (wrapper->action == Actions::Game::GAME_EXIT)
				exit(0); //TODO here should be a new state for closing
		}
	}
}