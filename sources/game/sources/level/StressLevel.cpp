#include "StressLevel.h"
#include "geometry/mesh/MeshLoader.h"
#include "geometry/mesh/MeshResources.h"
#include "texture/TextureLoader.h"
#include "texture/TextureResources.h"
#include "shaders/ShaderLoader.h"
#include "shaders/ShaderResources.h"
#include "animation/AnimDataResources.h"
#include "animation/AnimDataLoader.h"
#include "global/GlobalData.h"
#include "global/GlobalPaths.h"
#include "video/Painter.h"
#include "keys/ResourceKeyCollection.h"
#include "../defines/ResourceDefines.h"
#include "shaders/ShaderDefines.h"



StressLevel::StressLevel()
{

}

StressLevel::StressLevel(const StressLevel& copy)
{

}

StressLevel::~StressLevel()
{
	for (int i = 0; i < maxim; i++)
		delete bird[i];

	delete[] bird;
}

void StressLevel::Init()
{
	MeshLoader* mesh_loader = MeshLoader::GetInstance();
	MeshRes* mesh_res = MeshRes::GetInstance();
	TexLoader* tex_loader = TexLoader::GetInstance();
	TexRes* tex_res = TexRes::GetInstance();
	AnimDataRes* anim_res = AnimDataRes::GetInstance();
	AnimDataLoader* anim_loader = AnimDataLoader::GetInstance();
	ShaderLoader* shader_loader = ShaderLoader::GetInstance();
	ShaderRes* shader_res = ShaderRes::GetInstance();

	ResourceKeyCollection* resKeyColl = ResourceKeyCollection::GetInstance();

	/* Load a test texture */
	tex_res->Add((Texture*)tex_loader->Load(textures_path + resKeyColl->GetNameByKey(KEY_TEXTURE, RESOURCE_TEXTURE_ID_BIRD)), RESOURCE_TEXTURE_ID_BIRD);

	/* Load animations */
	anim_res->Add((AnimData*)anim_loader->Load(animation_path + resKeyColl->GetNameByKey(KEY_ANIMATION, RESOURCE_ANIMATION_ID_BIRD)), RESOURCE_ANIMATION_ID_BIRD);

	/* Load the shaders */
	shader_res->AddShaderPair((ShaderPair*)shader_loader->Load(shaders_path + resKeyColl->GetNameByKey(KEY_SHADER, SHADER_ID_BASIC_TEXTURING)),
							   SHADER_ID_BASIC_TEXTURING);


	unsigned int program_id = shader_res->RetriveProgramID(SHADER_ID_BASIC_TEXTURING);

	
	Painter::GetInstance()->SelectShader(program_id);
	Painter::SetActiveTexture(program_id, "s_texture");

	Painter::EnableMeshLocation(Painter::GetInstance()->GetMeshLocation());
	Painter::EnableTextureLocation(Painter::GetInstance()->GetTexLocation());


	Texture* texture;
	AnimData* animation;


	/* Get resources for the bird */
	animation = anim_res->Retrive(RESOURCE_ANIMATION_ID_BIRD);
	texture = tex_res->Retrive(RESOURCE_TEXTURE_ID_BIRD);

	/* TODO Create the test objects */
	bird = new BirdObject*[maxim];


	//TODO Comment this as I need an GameObjectPackage when constructing the bird entity
	//A solution will be to read the actual bird from a level file
	/*for (int i = 0; i < maxim; i++)
	{
		bird[i] = new BirdEntity(texture, program_id);
		bird[i]->SetPosition(rand() % (WORLD_ASP_RATIO_X * VIRTUAL_WORLD_MULTIPLIER) + 1,
			rand() % (WORLD_ASP_RATIO_Y * VIRTUAL_WORLD_MULTIPLIER) + 1);  //TODO - no not use such absolute values, maybe the measurement of the virtual world will change at some point and them I will be forced to do many changes
	}*/
}

void StressLevel::Update()
{
	for (int i = 0; i < maxim; i++)
		bird[i]->Update();
}

void StressLevel::Draw()
{
	/* Clear the color buffer */
	Painter::ClearScreen();

	for (int i = 0; i < maxim; i++)
	{
		bird[i]->PreDraw();
		bird[i]->Draw();
	}
}