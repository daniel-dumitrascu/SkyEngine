#ifndef PLATFORM_INPUT
#define PLATFORM_INPUT

#include <vector>
#include "Device.h"
#include "InputEventBatch.h"
#include <memory>

class PlatformInput
{
	public:
		static PlatformInput* GetInstance();

	public:
		static std::vector<std::unique_ptr<Device>> m_available_devices;
		static InputEventBatch inputBatch;

	private:
		PlatformInput();
		PlatformInput(const PlatformInput& copy) = delete;
		~PlatformInput() = default;

		PlatformInput& operator = (const PlatformInput& copy) {};
};

#endif