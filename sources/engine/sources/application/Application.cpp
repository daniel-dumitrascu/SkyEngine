#include "Application.h"
#include "keys/ResourceKeyCollection.h"
#include "shaders/ShaderDefines.h"


Application::Application() : is_running(false) 
{
	ResourceKeyCollection* keyCollection = ResourceKeyCollection::GetInstance();

	/* Adding the engine default shader keys */
	keyCollection->AddKey(KEY_SHADER, SHADER_ID_BASIC, "basic");
	keyCollection->AddKey(KEY_SHADER, SHADER_ID_BASIC_TEXTURING, "rend_tex");
	keyCollection->AddKey(KEY_SHADER, SHADER_ID_PRIMITIVE, "primitive");
}