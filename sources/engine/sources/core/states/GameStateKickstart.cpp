#include "GameStateKickstart.h"
#include "geometry/mesh/MeshLoader.h"
#include "geometry/mesh/MeshResources.h"
#include "texture/TextureLoader.h"
#include "texture/TextureResources.h"
#include "shaders/ShaderLoader.h"
#include "shaders/ShaderResources.h"
#include "keys/ResourceKeyCollection.h"
#include "defines/ResourceDefines.h"
#include "global/GlobalPaths.h"
#include "global/GlobalData.h"
#include "GameStateMainMenu.h"
#include "video/Painter.h"
#include "shaders/ShaderDefines.h"
#include "GameStateManager.h"


GameStateKickstart::GameStateKickstart() : is_done_loading(false), 
                               m_splash_screen(NULL), 
							   m_splash_timer(0500)
{
	stateID = GAME_STATE_KICKSTART;
}

GameStateKickstart::~GameStateKickstart()
{

}

void GameStateKickstart::ResumeState()
{
	/* Set the game keys */
	ResourceKeyCollection* resourceKeyCollection = ResourceKeyCollection::GetInstance();

	/* Adding the mesh keys */
	resourceKeyCollection->AddKey(KEY_TILE, RESOURCE_MESH_ID_CRATE, "crate.mesh");
	resourceKeyCollection->AddKey(KEY_TILE, RESOURCE_MESH_ID_PLAYER, "player.mesh");
	resourceKeyCollection->AddKey(KEY_TILE, RESOURCE_MESH_ID_WALL, "wall.mesh");
	resourceKeyCollection->AddKey(KEY_TILE, RESOURCE_MESH_ID_FULLSCREEN, "fullscreen.mesh");
	resourceKeyCollection->AddKey(KEY_TILE, RESOURCE_MESH_ID_GRASS, "grass.mesh");

	/* Adding the animation keys */
	resourceKeyCollection->AddKey(KEY_ANIMATION, RESOURCE_ANIMATION_ID_BIRD, "bird_fly");
	resourceKeyCollection->AddKey(KEY_ANIMATION, RESOURCE_ANIMATION_ID_SOLDIER, "soldier");

	/* Adding the texture keys */
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_BIRD, "bird_atlas.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_PLAYER, "player.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_GAME, "game.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_ZOMBIE, "zombie.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_MOUNTAIN, "mountain.tga");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_CRATE, "crate.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_WALL, "wall.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_SPLASHSCREEN, "splash.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_MAINMENU, "main_menu.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_SOLDIER, "soldier.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_BACKGROUND, "background.png");
	resourceKeyCollection->AddKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_GRASS, "grass.png");

	MeshRes::GetInstance()->Add((WireFrame*)MeshLoader::GetInstance()->Load(meshes_path + resourceKeyCollection->GetNameByKey(KEY_TILE, RESOURCE_MESH_ID_FULLSCREEN)), RESOURCE_MESH_ID_FULLSCREEN);
	TexRes::GetInstance()->Add((Texture*)TexLoader::GetInstance()->Load(textures_path + resourceKeyCollection->GetNameByKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_SPLASHSCREEN)), RESOURCE_TEXTURE_ID_SPLASHSCREEN);
	ShaderRes::GetInstance()->AddShaderPair((ShaderPair*)ShaderLoader::GetInstance()->Load(shaders_path + resourceKeyCollection->GetNameByKey(KEY_SHADER, SHADER_ID_BASIC)), SHADER_ID_BASIC);

	/***********************************************************************************************************************/
	unsigned int program_id = ShaderRes::GetInstance()->RetriveProgramID(SHADER_ID_BASIC);

	// move them in DrawScheme
	// for every shader pair :)
	// I call them once in init and then send the info as mesh_id and tex_id to every object in the scene

	//TODO call them each time I need to draw objects 
	//the functions will be called to every object group from the scenne that is assigned to a shader pair
	Painter::GetInstance()->SelectShader(program_id);
	Painter::SetActiveTexture(program_id, "s_texture");

	Painter::EnableMeshLocation(Painter::GetInstance()->GetMeshLocation());
	Painter::EnableTextureLocation(Painter::GetInstance()->GetTexLocation());
	/***********************************************************************************************************************/

	m_splash_timer.Start();
}

void GameStateKickstart::SuspendState()
{

}

void GameStateKickstart::UpdateState()
{
	if (!m_splash_timer.IsExceeded() || !is_done_loading)
	{
		if (m_splash_screen)
		    m_splash_screen->Update();
		else
		{
			MeshRes* mesh_res = MeshRes::GetInstance();
			TexLoader* tex_loader = TexLoader::GetInstance();
			TexRes* tex_res = TexRes::GetInstance();
			ShaderRes* shader_res = ShaderRes::GetInstance();

			ResourceKeyCollection* resourceKeyCollection = ResourceKeyCollection::GetInstance();

			/* load the splash screen and menu resources */	
			tex_res->Add((Texture*)tex_loader->Load(textures_path + resourceKeyCollection->GetNameByKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_MAINMENU)), RESOURCE_TEXTURE_ID_MAINMENU);
			
			unsigned int program_id = shader_res->RetriveProgramID(SHADER_ID_BASIC);

			WireFrame* mesh;
			Texture* texture;

			/* Get resources for the splashscreen */
			mesh = mesh_res->Retrive(RESOURCE_MESH_ID_FULLSCREEN);
			texture = tex_res->Retrive(RESOURCE_TEXTURE_ID_SPLASHSCREEN);

			m_splash_screen = new SplashScreen(mesh, texture, program_id);
			m_splash_screen->Init();

			return;
		}

		/*TODO - here you can also load sounds, tex and other gameplay resources */

		is_done_loading = true;
	}
	else
	{
		GameStateManager::PushState(new GameStateMainMenu);
	}
}

void GameStateKickstart::RenderState()
{
	m_splash_screen->PreDraw();
	m_splash_screen->Draw();
}