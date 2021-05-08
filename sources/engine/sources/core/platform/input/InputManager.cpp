#include "InputManager.h"
#include "DeviceDefinitions.h"
#include "../../input/Controllable.h"


InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

InputManager::~InputManager()
{
	subscribers.FreeAll();
}

int InputManager::AddSubscriber(Controllable* subs)
{
	return (subs != nullptr) ? subscribers.Occupy(subs) : -1;
}

void InputManager::RemoveSubscriber(int id)
{
	subscribers.Free(id);
}

void InputManager::Update()
{
	if(!PlatformInput::inputBatch.isEmpty())
	{
		// Send the key batch to all the subscribers
		for(int i=0; i < subscribers.Count() && !subscribers.IsSlotFree(i); ++i)
		{
			if(subscribers.Retrive(i) != nullptr)
				subscribers.Retrive(i)->InputActionNotify(PlatformInput::inputBatch);
			else
				std::cout << "[ERROR] Retrived subscriber is null." << std::endl;
		}
	}
}