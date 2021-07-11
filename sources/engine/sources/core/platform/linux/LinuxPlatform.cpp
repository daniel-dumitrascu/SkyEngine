#include "LinuxPlatform.h"
#include "logging/Logging.h"
#include "../input/DeviceDefinitions.h"
#include "../input/PlatformInput.h"
#include "../input/InputEventBatch.h"
#include "../input/InputManager.h"
#include "stream/IClearFile.h"
#include "global/GlobalData.h"
#include "../../../system/System.h"
#include <iostream>

#if(GRAPHICS_OPENGL_LATEST)
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif

Platform* LinuxPlatform::GetPlatformHandle()
{
    if (!m_platform)
		 m_platform = new LinuxPlatform;

	return m_platform;
}

void LinuxPlatform::InitPlatform(void** screen_handle)
{
    // Load saved settings
	LoadPlatformSettings(); 

    if (!is_win_constr)
	{
		// Construct the main window of the app
		LinuxConstructWindow();

		// We are going to initiate the PlatformInput before using it
		// and select the available input devices
		PlatformInput* inputInst = PlatformInput::GetInstance();
		if (inputInst->m_available_devices[DEVICE_KEYBOARD] != nullptr)
		{
			platformAvailableInputDevices.push_back(&LinuxPlatform::checkKeyInput);
		}
			
		if (inputInst->m_available_devices[DEVICE_MOUSE] != nullptr)
		{
			platformAvailableInputDevices.push_back(&LinuxPlatform::checkMouseInput);
		}

		is_win_constr = true;
	}

	*screen_handle = (void*)m_window;
}

void LinuxPlatform::UpdatePlatform()
{
	glfwPollEvents();
	CheckInput();
	InputManager::GetInstance()->Update();
}

bool LinuxPlatform::IsRunning() 
{ 
	return !glfwWindowShouldClose((GLFWwindow*)m_window);
}

void LinuxPlatform::CheckInput()
{
	static PlatformInput* platformer_input = PlatformInput::GetInstance();
	InputEventBatch frameInputBatch;
	// TODO through this method I make allocations and deallocations per frame
	// Use inputBatch and reset it here before taking the input
	// rather than deleting and reallocating the internal batch vectors, I would prefer to reset them
	// maybe by a call to clear()

	for (int i = 0; i < platformAvailableInputDevices.size(); ++i)
		(this->*(platformAvailableInputDevices[i]))(frameInputBatch);

	//TODO don't like this copying
	platformer_input->inputBatch = frameInputBatch;	
}

void LinuxPlatform::checkKeyInput(InputEventBatch& frameInputBatch)
{
	static BinaryArray& keysStatus = PlatformInput::GetInstance()->m_available_devices[DEVICE_KEYBOARD]->m_keys_status;

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_UP))
	{
		frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_UP, KEYBOARD_BUTTON_PRESS);
		keysStatus.SetFlagON(BUTTON_KEYBOARD_UP);
	}
	else
	{
		// This is neaded so that we don't send an InputEvent with a release status each frame
		if (keysStatus.IsFlagON(BUTTON_KEYBOARD_UP))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_UP, KEYBOARD_BUTTON_RELEASE);
			keysStatus.SetFlagOFF(BUTTON_KEYBOARD_UP);
		}
	}


	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_DOWN))
	{
		frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_DOWN, KEYBOARD_BUTTON_PRESS);
		keysStatus.SetFlagON(BUTTON_KEYBOARD_DOWN);
	}
	else
	{
		// This is neaded so that we don't send an InputEvent with a release status each frame
		if (keysStatus.IsFlagON(BUTTON_KEYBOARD_DOWN))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_DOWN, KEYBOARD_BUTTON_RELEASE);
			keysStatus.SetFlagOFF(BUTTON_KEYBOARD_DOWN);
		}
	}


	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_LEFT))
	{
		frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_LEFT, KEYBOARD_BUTTON_PRESS);
		keysStatus.SetFlagON(BUTTON_KEYBOARD_LEFT);
	}
	else
	{
		// This is neaded so that we don't send an InputEvent with a release status each frame
		if (keysStatus.IsFlagON(BUTTON_KEYBOARD_LEFT))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_LEFT, KEYBOARD_BUTTON_RELEASE);
			keysStatus.SetFlagOFF(BUTTON_KEYBOARD_LEFT);
		}
	}


	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_RIGHT))
	{
		frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_RIGHT, KEYBOARD_BUTTON_PRESS);
		keysStatus.SetFlagON(BUTTON_KEYBOARD_RIGHT);
	}
	else
	{
		// This is neaded so that we don't send an InputEvent with a release status each frame
		if (keysStatus.IsFlagON(BUTTON_KEYBOARD_RIGHT))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_RIGHT, KEYBOARD_BUTTON_RELEASE);
			keysStatus.SetFlagOFF(BUTTON_KEYBOARD_RIGHT);
		}
	}

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_1))
	{
		if (!keysStatus.IsFlagON(BUTTON_KEYBOARD_1))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_1, KEYBOARD_BUTTON_PRESS);
			keysStatus.SetFlagON(BUTTON_KEYBOARD_1);
		}
	}
	else
	{
		keysStatus.SetFlagOFF(BUTTON_KEYBOARD_1);
	}

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_2))
	{
		if (!keysStatus.IsFlagON(BUTTON_KEYBOARD_2))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_2, KEYBOARD_BUTTON_PRESS);
			keysStatus.SetFlagON(BUTTON_KEYBOARD_2);
		}
	}
	else
	{
		keysStatus.SetFlagOFF(BUTTON_KEYBOARD_2);
	}

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_3))
	{
		if (!keysStatus.IsFlagON(BUTTON_KEYBOARD_3))
		{
			frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_3, KEYBOARD_BUTTON_PRESS);
			keysStatus.SetFlagON(BUTTON_KEYBOARD_3);
		}
	}
	else
	{
		keysStatus.SetFlagOFF(BUTTON_KEYBOARD_3);
	}

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_SPACE))
	{
		frameInputBatch.addData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_SPACE, KEYBOARD_BUTTON_PRESS);
	}
}

void LinuxPlatform::checkMouseInput(InputEventBatch& frameInputBatch)
{
	if (glfwGetMouseButton((GLFWwindow*)m_window, GLFW_MOUSE_BUTTON_LEFT))
	{
		frameInputBatch.addData(DEVICE_MOUSE, BUTTON_MOUSE_LEFT, KEYBOARD_BUTTON_PRESS);
	}
	if (glfwGetMouseButton((GLFWwindow*)m_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		frameInputBatch.addData(DEVICE_MOUSE, BUTTON_MOUSE_RIGHT, KEYBOARD_BUTTON_PRESS);
	}
}

LinuxPlatform::LinuxPlatform() : log("LinuxPlatform"), is_win_constr(false)
{

}

LinuxPlatform::~LinuxPlatform()
{
    delete m_platform;
	m_platform = NULL;
}

void LinuxPlatform::LoadPlatformSettings()
{
    AspectRatio aspect_ratio;
	DisplayResolution resolution;

	GetPlatformSettings(aspect_ratio, resolution);	

	SetWindowAspectRatio(aspect_ratio);
	SetWindowResolution(resolution);
}

void LinuxPlatform::GetPlatformSettings(AspectRatio& aspect_ratio, DisplayResolution& resolution)
{
	/* Get aspect ratio */
	aspect_ratio.x = WINDOWS_ASP_RATIO_X;
	aspect_ratio.y = WINDOWS_ASP_RATIO_Y;

	/* Compute screen resolution using the multiplier value */
	resolution.width = aspect_ratio.x * WINDOWS_SCREEN_MULTIPLIER;
	resolution.height = aspect_ratio.y * WINDOWS_SCREEN_MULTIPLIER;
}

void LinuxPlatform::LinuxConstructWindow()
{
	log.message("Creating the Linux window", Logging::MSG_INFO);

	m_window = glfwCreateWindow(m_resolution.width, m_resolution.height, "The Purge Game", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(-1);
	}
}