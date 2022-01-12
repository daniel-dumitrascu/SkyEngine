#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "Device.h"
#include "PlatformInput.h"
#include "input/Controllable.h"
#include "../../utils/FastAccessCollection.h"

class InputManager
{
	public:

		static InputManager* GetInstance();
				
		int AddSubscriber(Controllable* subs);
		void RemoveSubscriber(int id);
		void Update();

	private:

		InputManager() {};
		~InputManager();

		InputManager(const InputManager& copy) = delete;
		InputManager& operator = (const InputManager& copy) = delete;

	private:

		FastAccessCollection<Controllable>	subscribers;
};

#endif