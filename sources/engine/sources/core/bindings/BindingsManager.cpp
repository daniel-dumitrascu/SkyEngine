#include "BindingsManager.h"
#include "../platform/input/DeviceDefinitions.h"
#include "../actions/Actions.h"
#include "../input/InputHandleProfiles.h"

BindingsManager& BindingsManager::GetInstance()
{
    static BindingsManager instance;
    return instance;
}

BindingsManager::BindingsManager()
{
	ConstructBindings();
}

BindingsManager::~BindingsManager()
{
	// Deallocate the layers
	for (int i = 0; i < bindingsForDifferentLayers.size(); ++i)
	{
		delete bindingsForDifferentLayers[i];
	}
}

BindingCollection* BindingsManager::GetLayerBinding(int layer)
{
	std::unordered_map<int, BindingCollection*>::iterator ite = bindingsForDifferentLayers.find(layer);
	return (ite == bindingsForDifferentLayers.end()) ? nullptr : ite->second;
}

void BindingsManager::ConstructBindings()
{
	// Menu profile
	BindingCollection* layer = new BindingCollection();
	layer->AddBinding(BUTTON_KEYBOARD_ESC, Actions::Game::GAME_EXIT);
	layer->AddBinding(BUTTON_MOUSE_LEFT, Actions::Menu::MENU_CLICK);
	layer->AddBinding(BUTTON_MOUSE_RIGHT, Actions::Menu::MENU_CLICK);
	layer->AddBinding(BUTTON_MOUSE_MIDDLE, Actions::Menu::MENU_CLICK);

	bindingsForDifferentLayers.insert(std::unordered_map<int, BindingCollection*>::value_type(INPUT_HANDLE_PROFILE_MENU, layer));

	// Level profile
	layer = new BindingCollection();
	layer->AddBinding(BUTTON_KEYBOARD_1, Actions::Debug::DEBUG_GRID_DRAW);
	layer->AddBinding(BUTTON_KEYBOARD_2, Actions::Debug::DEBUG_OBJECT_TILE_MAPPING);
	layer->AddBinding(BUTTON_KEYBOARD_3, Actions::Debug::DEBUG_OBJECT_RECTANGLE);

	bindingsForDifferentLayers.insert(std::unordered_map<int, BindingCollection*>::value_type(INPUT_HANDLE_PROFILE_LEVEL, layer));

	// Game object profile
	layer = new BindingCollection();
	layer->AddBinding(BUTTON_KEYBOARD_UP, Actions::Gameplay::GAMEPLAY_MOVE_UP);
	layer->AddBinding(BUTTON_KEYBOARD_DOWN, Actions::Gameplay::GAMEPLAY_MOVE_DOWN);
	layer->AddBinding(BUTTON_KEYBOARD_LEFT, Actions::Gameplay::GAMEPLAY_MOVE_LEFT);
	layer->AddBinding(BUTTON_KEYBOARD_RIGHT, Actions::Gameplay::GAMEPLAY_MOVE_RIGHT);
	layer->AddBinding(BUTTON_KEYBOARD_ESC, Actions::Game::GAME_EXIT);
	layer->AddBinding(BUTTON_KEYBOARD_SPACE, Actions::Gameplay::GAMEPLAY_ATTACK);

	bindingsForDifferentLayers.insert(std::unordered_map<int, BindingCollection*>::value_type(INPUT_HANDLE_PROFILE_GAMEOBJECT, layer));
}