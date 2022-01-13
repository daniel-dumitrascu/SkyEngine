#include "GameStateMainMenu.h"
#include "geometry/mesh/MeshLoader.h"
#include "geometry/mesh/MeshResources.h"
#include "texture/TextureLoader.h"
#include "texture/TextureResources.h"
#include "shaders/ShaderLoader.h"
#include "shaders/ShaderResources.h"
#include "settings/SettingsLoader.h"
#include "menu/MainMenu.h"
#include "platform/input/InputManager.h"
#include "global/GlobalPaths.h"
#include "global/GlobalData.h"
#include "video/Painter.h"


//TODO This implementation will be changes once I introduce a framework for in-game menu

GameStateMainMenu::GameStateMainMenu()
{
	stateID = GAME_STATE_MAINMENU;
}

GameStateMainMenu::~GameStateMainMenu()
{
	UnsubscribeFromInput();
}

void GameStateMainMenu::ResumeState()
{
	const std::string& shaderPath = SettingsLoader::GetInstance()->GetValue("defaultResources.menu.shader");
	unsigned int program_id = ShaderRes::GetInstance()->Retrive(shaderPath);

	// TODO 
	// Move these calls in DrawScheme
	// for every shader pair :)
	// I call them once in init and then send the info as mesh_id and tex_id to every object in the scene

	//TODO call them each time I need to draw objects 
	//the functions will be called to every object group from the scenne that is assigned to a shader pair
	/*************************************************************************/
	Painter::GetInstance()->SelectShader(program_id);
	Painter::SetActiveTexture(program_id, "s_texture");

	Painter::EnableMeshLocation(Painter::GetInstance()->GetMeshLocation());
	Painter::EnableTextureLocation(Painter::GetInstance()->GetTexLocation());
	/*************************************************************************/
}

void GameStateMainMenu::SuspendState()
{
	UnsubscribeFromInput();
}

void GameStateMainMenu::UpdateState()
{
	if (m_main_menu)
	{
		m_main_menu->Update();
	}
	else
	{
		const std::string& shaderPath = SettingsLoader::GetInstance()->GetValue("defaultResources.menu.shader");
		unsigned int program_id = ShaderRes::GetInstance()->Retrive(shaderPath);

		MeshRes* mesh_res = MeshRes::GetInstance();
		TexRes* tex_res = TexRes::GetInstance();
		WireFrame* mesh;
		Texture* texture;
		
		/* Get resources for the splashscreen */
		mesh = mesh_res->Retrive(SettingsLoader::GetInstance()->GetValue("defaultResources.menu.mesh"));
		texture = tex_res->Retrive(SettingsLoader::GetInstance()->GetValue("defaultResources.menu.texture"));

		m_main_menu = std::make_unique<MainMenu>(mesh, texture, program_id);
		m_main_menu->Init();
		InputManager* input_manager = InputManager::GetInstance();
		int subId = input_manager->AddSubscriber((Controllable*)m_main_menu.get());
		if(subId == -1)
			std::cout << "[ERROR] Problem when addind the menu as input subscriber" << std::endl;
		else
			((Controllable*)m_main_menu.get())->SetSubscriberId(subId);
			
		return;
	}
}

void GameStateMainMenu::RenderState()
{
	m_main_menu->PreDraw();
	m_main_menu->Draw();
}

void GameStateMainMenu::UnsubscribeFromInput()
{
	InputManager* input_manager = InputManager::GetInstance();
	input_manager->RemoveSubscriber(((Controllable*)m_main_menu.get())->GetSubscriberId());
	((Controllable*)m_main_menu.get())->SetSubscriberId(-1);
}