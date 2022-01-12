#include "BindingsManager.h"
#include "../platform/input/DeviceDefinitions.h"
#include "../actions/Actions.h"
#include "../input/InputHandleProfiles.h"
#include "../math/Vector.h"
#include <memory>

BindingsManager& BindingsManager::GetInstance()
{
    static BindingsManager instance;
    return instance;
}

BindingsManager::BindingsManager()
{
	ConstructBindings();
}

BindingCollection* BindingsManager::GetLayerBinding(int layer)
{
	std::unordered_map<int, std::unique_ptr<BindingCollection>>::iterator ite = bindingsForDifferentLayers.find(layer);
	return (ite == bindingsForDifferentLayers.end()) ? nullptr : ite->second.get();
}

void BindingsManager::ConstructBindings()
{
	// Menu profile
	std::unique_ptr<BindingCollection> layer(new BindingCollection());
	layer->AddBinding(BUTTON_KEYBOARD_ESC, Actions::Game::GAME_EXIT);
	layer->AddBinding(BUTTON_MOUSE_LEFT, Actions::Menu::MENU_CLICK);
	layer->AddBinding(BUTTON_MOUSE_RIGHT, Actions::Menu::MENU_CLICK);
	layer->AddBinding(BUTTON_MOUSE_MIDDLE, Actions::Menu::MENU_CLICK);

	bindingsForDifferentLayers
		.insert(std::unordered_map<int, std::unique_ptr<BindingCollection>>::value_type(INPUT_HANDLE_PROFILE_MENU, std::move(layer)));

	// Level profile
	layer.reset(new BindingCollection());
	layer->AddBinding(BUTTON_KEYBOARD_1, Actions::Debug::DEBUG_GRID_DRAW);
	layer->AddBinding(BUTTON_KEYBOARD_2, Actions::Debug::DEBUG_OBJECT_SECTOR_MAPPING);
	layer->AddBinding(BUTTON_KEYBOARD_3, Actions::Debug::DEBUG_OBJECT_RECTANGLE);

	bindingsForDifferentLayers
		.insert(std::unordered_map<int, std::unique_ptr<BindingCollection>>::value_type(INPUT_HANDLE_PROFILE_LEVEL, std::move(layer)));

	// Game object profile
	layer.reset(new BindingCollection());
	layer->AddBinding(BUTTON_KEYBOARD_UP, Actions::Gameplay::GAMEPLAY_MOVE_UP, std::make_shared<vec_3x>(vec_3x(0.0f, 1.0f, 0.0f)));
	layer->AddBinding(BUTTON_KEYBOARD_DOWN, Actions::Gameplay::GAMEPLAY_MOVE_DOWN, std::make_shared<vec_3x>(vec_3x(0.0f, -1.0f, 0.0f)));
	layer->AddBinding(BUTTON_KEYBOARD_LEFT, Actions::Gameplay::GAMEPLAY_MOVE_LEFT, std::make_shared<vec_3x>(vec_3x(-1.0f, 0.0f, 0.0f)));
	layer->AddBinding(BUTTON_KEYBOARD_RIGHT, Actions::Gameplay::GAMEPLAY_MOVE_RIGHT, std::make_shared<vec_3x>(vec_3x(1.0f, 0.0f, 0.0f)));
	layer->AddBinding(BUTTON_KEYBOARD_ESC, Actions::Game::GAME_EXIT);
	layer->AddBinding(BUTTON_KEYBOARD_SPACE, Actions::Gameplay::GAMEPLAY_ATTACK);

	bindingsForDifferentLayers
		.insert(std::unordered_map<int, std::unique_ptr<BindingCollection>>::value_type(INPUT_HANDLE_PROFILE_GAMEOBJECT, std::move(layer)));
}