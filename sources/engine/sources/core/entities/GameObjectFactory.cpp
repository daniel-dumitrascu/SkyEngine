#include "GameObjectFactory.h"
#include "GameObjectDefines.h"
#include "utils/UniqueGenerator.h"
#include "primitive/Line.h"
#include "primitive/GameRectangle.h"
#include "geometry/mesh/MeshResources.h"
#include "geometry/mesh/MeshLoader.h"
#include "texture/TextureResources.h"
#include "texture/TextureLoader.h"
#include "animation/AnimDataResources.h"
#include "animation/AnimDataLoader.h"
#include "shaders/ShaderLoader.h"
#include "global/GlobalPaths.h"
#include "entities/Background.h"
#include "entities/StaticObject.h"
#include "entities/Player.h"

GameObjectFactory* GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return (&instance);
}

GameObject* GameObjectFactory::CreateGameObject(GameObjectPackage& objPack)
{
	if (objPack.m_type == GAME_OBJECT_ID_LINE)
	{
		return CreateGameLine(objPack.m_startPoint, objPack.m_endPoint, objPack.m_thickness, objPack.m_color);
	}

	if (objPack.m_type == GAME_OBJECT_ID_RECT)
	{
		return CreateGameRectangle(objPack.m_pointTopLeft, objPack.m_pointBottomRight, objPack.m_color);
	}

	WireFrame* mesh = GetMesh(objPack);
	Texture* tex = GetTexture(objPack);
	int program = GetProgram(objPack);

	GameObject* obj = nullptr;

	if (mesh && tex && program != 0)
	{
		if (objPack.m_type == GAME_OBJECT_ID_PLAYER)
		{
			obj = new Player(mesh, tex, program, objPack.m_position.elem[0], objPack.m_position.elem[1], objPack.m_scale, objPack.m_zBuffer);

#if(DEBUG_SECTION)
			GameLine *leftOutline = nullptr;
			GameLine *rightOutline = nullptr;
			GameLine *topOutline = nullptr;
			GameLine *bottomOutline = nullptr;
			ConstructDebugOutlines(obj, &leftOutline, &rightOutline, &topOutline, &bottomOutline);
			obj->SetDebugOutlines(leftOutline, rightOutline, topOutline, bottomOutline);
#endif
		}
		else if (objPack.m_type == GAME_OBJECT_ID_STATIC_BLOCK)
		{
			obj = new StaticObject(mesh, tex, program, objPack.m_position.elem[0], objPack.m_position.elem[1], objPack.m_scale, objPack.m_zBuffer);

#if(DEBUG_SECTION)
			GameLine *leftOutline = nullptr;
			GameLine *rightOutline = nullptr;
			GameLine *topOutline = nullptr;
			GameLine *bottomOutline = nullptr;
			ConstructDebugOutlines(obj, &leftOutline, &rightOutline, &topOutline, &bottomOutline);
			obj->SetDebugOutlines(leftOutline, rightOutline, topOutline, bottomOutline);
#endif
		}
		else if (objPack.m_type == GAME_OBJECT_ID_BACKGROUND)
		{
			obj = new Background(mesh, tex, program, objPack.m_position.elem[0], objPack.m_position.elem[1], objPack.m_scale);
		}
	}

	// Set rendable flag
	if (objPack.m_renderable)
		obj->SetFlagON(GameObjectFlags::OBJECT_IS_RENDERABLE);
	else
		obj->SetFlagOFF(GameObjectFlags::OBJECT_IS_RENDERABLE);

	// Set collidable flag
	if (objPack.m_collidable)
		obj->SetFlagON(GameObjectFlags::OBJECT_IS_COLLIDABLE);
	else
		obj->SetFlagOFF(GameObjectFlags::OBJECT_IS_COLLIDABLE);

	// Set contralable flag
	if (objPack.m_controllable)
		obj->SetFlagON(OBJECT_IS_CONTROLLABLE);
	else
		obj->SetFlagOFF(OBJECT_IS_CONTROLLABLE);


	return obj;


	//TODO - See what functionality these classes have and try to integrate it into GameObject
	//After that we can delete them
	
	/*case GAME_OBJECT_ID_BIRD:
	{
		//TODO - for animations, I will send this param exactly the same as I send the WireFrame
		AnimData* anim = GetAnimation(objPack);
		Texture* tex = GetTexture(objPack);
		int program = GetProgram(objPack);

		if (anim && tex && program != 0)
		{
			obj = new BirdObject(tex, program, objPack.m_position.elem[0], objPack.m_position.elem[1], objPack.m_scale, objPack.m_id);
			UniqueGenerator::Instance().AddIDToMemory(objPack.m_id);
		}

		break;
	}*/
	
	/*case GAME_OBJECT_ID_SOLDIER:
	{
		AnimData* anim = GetAnimation(objPack);
		Texture* tex = GetTexture(objPack);
		int program = GetProgram(objPack);

		if (anim && tex && program != 0)
		{
			obj = new SoldierObject(tex, program, objPack.m_position.elem[0], objPack.m_position.elem[1], objPack.m_scale, objPack.m_id);
			UniqueGenerator::Instance().AddIDToMemory(objPack.m_id);
		}

		break;
	}*/
	
	/*case GAME_OBJECT_ID_MOVING_OBJECT:
	{
		WireFrame* mesh = GetMesh(objPack);
		Texture* tex = GetTexture(objPack);
		int program = GetProgram(objPack);

		if (mesh && tex && program != 0)
		{
			obj = new MovingObject(mesh, tex, program, objPack.m_position.elem[0], objPack.m_position.elem[1], objPack.m_scale, objPack.m_id);
			UniqueGenerator::Instance().AddIDToMemory(objPack.m_id);
		}

		break;
	}*/
}

Camera* GameObjectFactory::CreateCamera(const CameraPackage& cameraPack)
{
	return new Camera(cameraPack.position, cameraPack.rotation);
}

GameObject* GameObjectFactory::CreateGameLine(vec_2x& startPoint, vec_2x& endPoint, int thickness, vec_4x& color)
{
	Line line(startPoint, endPoint, thickness);
	return new GameLine(line, color);
}

GameObject* GameObjectFactory::CreateGameRectangle(vec_2x& recLeftTop, vec_2x& recRightBottom, vec_4x& color)
{
	return new GameRectangle(recLeftTop, recRightBottom, color);
}

WireFrame* GameObjectFactory::GetMesh(GameObjectPackage& pack)
{
	/* Do we have this resource loaded? */
	/* If not, we need to load it */
	std::string fullpath = working_dir_path + "\\" + pack.m_meshPath;
	WireFrame* mesh = MeshRes::GetInstance()->Retrive(pack.m_meshPath);
	if (mesh == nullptr)
	{
		MeshRes::GetInstance()->Add(pack.m_meshPath, fullpath);
		mesh = MeshRes::GetInstance()->Retrive(pack.m_meshPath);
	}
		
	return mesh;
}

Texture* GameObjectFactory::GetTexture(GameObjectPackage& pack)
{
	/* Do we have this resource loaded? */
	/* If not, we need to load it */
	std::string fullpath = working_dir_path + "\\" + pack.m_texturePath;
	Texture* tex = TexRes::GetInstance()->Retrive(pack.m_texturePath);
	if (tex == nullptr)
	{
		TexRes::GetInstance()->Add(pack.m_texturePath, fullpath);
		tex = TexRes::GetInstance()->Retrive(pack.m_texturePath);
	}

	return tex;
}

AnimData* GameObjectFactory::GetAnimation(GameObjectPackage& pack)
{
	/* Do we have this resource loaded? */
	/* If not, we need to load it */
	std::string fullpath = working_dir_path + "\\" + pack.m_animationPath;
	AnimData* anim = AnimDataRes::GetInstance()->Retrive(pack.m_animationPath);
	if (anim == nullptr)
	{
		AnimDataRes::GetInstance()->Add(pack.m_animationPath, fullpath);
		anim = AnimDataRes::GetInstance()->Retrive(pack.m_animationPath);
	}

	return anim;
}

int GameObjectFactory::GetProgram(GameObjectPackage& pack)
{
	/* Do we have this resource loaded? */
	/* If not, we need to load it */
	std::string fullpath = working_dir_path + "\\" + pack.m_shaderPath;
	int program = ShaderRes::GetInstance()->Retrive(pack.m_shaderPath);
	if (!program)
	{
		ShaderRes::GetInstance()->Add(pack.m_shaderPath, fullpath);
		program = ShaderRes::GetInstance()->Retrive(pack.m_shaderPath);
	}

	return program;
}

#if(DEBUG_SECTION)
void GameObjectFactory::ConstructDebugOutlines(GameObject* obj, GameLine **leftOutline, GameLine **rightOutline, GameLine **topOutline, GameLine **bottomOutline)
{
	vec_4x lineColor;
	vec_2x startPoint;
	vec_2x endPoint;
	vector::vector_4x::SetVector(lineColor, 0.0f, 0.0f, 1.0f, 1.0f);
	Rectangle rect = obj->GetObjectWorldRect();

	vector::vector_2x::SetVector(startPoint, rect.GetLeft(), rect.GetTop());
	vector::vector_2x::SetVector(endPoint, rect.GetLeft(), rect.GetBottom());
	*leftOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);

	vector::vector_2x::SetVector(startPoint, rect.GetRight(), rect.GetTop());
	vector::vector_2x::SetVector(endPoint, rect.GetRight(), rect.GetBottom());
	*rightOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);

	vector::vector_2x::SetVector(startPoint, rect.GetLeft(), rect.GetTop());
	vector::vector_2x::SetVector(endPoint, rect.GetRight(), rect.GetTop());
	*topOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);

	vector::vector_2x::SetVector(startPoint, rect.GetLeft(), rect.GetBottom());
	vector::vector_2x::SetVector(endPoint, rect.GetRight(), rect.GetBottom());
	*bottomOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);
}
#endif