#pragma once
#include "../platform/input/InputEventBatch.h"
#include "InputHandleProfiles.h"
#include "../bindings/BindingsManager.h"


class Controllable
{
	public:

		Controllable(InputHandleProfile l) : layer(l) 
		{
			if (l == INPUT_HANDLE_PROFILE_NONE)
				return;

			inputToActionBindings = BindingsManager::GetInstance().GetLayerBinding(l);
			if (inputToActionBindings == nullptr)
			{
				std::cout << "[ERROR] Controllable - no valid bindings have been found" << std::endl;
			}
		}

		virtual ~Controllable() {};

		// We add the actions vector for the current frame
		virtual void InputActionNotify(const InputEventBatch& inputBatch) = 0;

		int GetSubscriberId() { return id; }
		void SetSubscriberId(int id) { this->id = id; }
 
	protected:

		// Having an ID of -1 means that the Controllable 
		// entity isn't subscribed to an input system
		int id = -1;

		// The layer which handles the input
		InputHandleProfile layer;

		// Bindings for the specified layer
		BindingCollection* inputToActionBindings = nullptr;
};