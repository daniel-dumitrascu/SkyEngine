#include "PlatformInput.h"
#include "DeviceDefinitions.h"

std::vector<Device*> PlatformInput::m_available_devices;
InputEventBatch PlatformInput::inputBatch;

PlatformInput* PlatformInput::GetInstance()
{
	static PlatformInput instance;
	return &instance;
}

PlatformInput::PlatformInput()
{
	/* Set the number of devices on windows platform */
	m_available_devices.reserve(DEVICE_COUNT);

	/* Detect the connected devices */
#if (WINDOWS_PLATFORM || LINUX_PLATFORM)		
	//TODO the actual detection will be platform dependent and will be done some day
	m_available_devices.insert(m_available_devices.begin() + DEVICE_KEYBOARD, 
								new Device(BUTTON_KEYBOARD_COUNT));
	m_available_devices.insert(m_available_devices.begin() + DEVICE_MOUSE, 
								new Device(BUTTON_MOUSE_COUNT));
#endif
}

PlatformInput::~PlatformInput()
{
#if (WINDOWS_PLATFORM || LINUX_PLATFORM)		
	//TODO the actual detection will be platform dependent and will be done some day
	delete m_available_devices[DEVICE_KEYBOARD];
	delete m_available_devices[DEVICE_MOUSE];
#endif
}
