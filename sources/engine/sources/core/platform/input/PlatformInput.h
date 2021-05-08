#ifndef PLATFORM_INPUT
#define PLATFORM_INPUT

#include <vector>
#include "Device.h"
#include "InputEventBatch.h"

class PlatformInput
{
	public:
		static PlatformInput* GetInstance();

	public:
		static std::vector<Device*> m_available_devices;
		static InputEventBatch inputBatch;

	private:
		PlatformInput();
		PlatformInput(const PlatformInput& copy) {};
		~PlatformInput();

		PlatformInput& operator = (const PlatformInput& copy) {};
};

#endif