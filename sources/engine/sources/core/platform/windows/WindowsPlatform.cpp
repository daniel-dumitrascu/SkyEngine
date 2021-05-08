#include "WindowsPlatform.h"
#include "stream/IClearFile.h"
#include "logging/Logging.h"
#include "../input/DeviceDefinitions.h"
#include "../input/PlatformInput.h"
#include "../input/InputEventBatch.h"
#include "../input/InputManager.h"
#include "stream/IClearFile.h"
#include "global/GlobalData.h"
#include "../../../system/System.h"

/*
 * This are needed for the window creation 
 * if we use the lastest OpenGL
 */
#if(GRAPHICS_OPENGL_LATEST)
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif

#include <string>
#include <sstream>
#include <windows.h>
#include <Windowsx.h>
#include <iostream>

Platform* WindowsPlatform::GetPlatformHandle()
{
	if (!m_platform)
		 m_platform = new WindowsPlatform;

	return m_platform;
}

void WindowsPlatform::InitPlatform(void** screen_handle)
{
	// Load saved settings 
	LoadPlatformSettings(); 

	if (!is_win_constr)
	{
		// Construct the main window of the app
		WindowsConstructWindow();

		// We are going to initiate the PlatformInput before using it
		// and select the available input devices
		PlatformInput* inputInst = PlatformInput::GetInstance();
		if (inputInst->m_available_devices[DEVICE_KEYBOARD] != nullptr)
		{
			platformAvailableInputDevices.push_back(&WindowsPlatform::checkKeyInput);
		}
			
		if (inputInst->m_available_devices[DEVICE_MOUSE] != nullptr)
		{
			platformAvailableInputDevices.push_back(&WindowsPlatform::checkMouseInput);
		}
			
		is_win_constr = true;
	}

	*screen_handle = (void*)m_window;
}

void WindowsPlatform::UpdatePlatform()
{
	glfwPollEvents();
	CheckInput();
	InputManager::GetInstance()->Update();
}

bool WindowsPlatform::IsRunning()
{
	return !glfwWindowShouldClose((GLFWwindow*)m_window);
}

void WindowsPlatform::CheckInput()
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

void WindowsPlatform::checkKeyInput(InputEventBatch& frameInputBatch)
{
	static BinaryArray& keysStatus = PlatformInput::GetInstance()->m_available_devices[DEVICE_KEYBOARD]->m_keys_status;

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_UP))
	{
		frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_UP);
	}
	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_DOWN))
	{
		frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_DOWN);
	}
	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_LEFT))
	{
		frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_LEFT);
	}
	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_RIGHT))
	{
		frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_RIGHT);
	}

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_1))
	{
		if (!keysStatus.IsFlagON(BUTTON_KEYBOARD_1))
		{
			frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_1);
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
			frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_2);
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
			frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_3);
			keysStatus.SetFlagON(BUTTON_KEYBOARD_3);
		}
	}
	else
	{
		keysStatus.SetFlagOFF(BUTTON_KEYBOARD_3);
	}

	if (glfwGetKey((GLFWwindow*)m_window, GLFW_KEY_SPACE))
	{
		frameInputBatch.addDeviceData(DEVICE_KEYBOARD, BUTTON_KEYBOARD_SPACE);
	}
}

void WindowsPlatform::checkMouseInput(InputEventBatch& frameInputBatch)
{
	if (glfwGetMouseButton((GLFWwindow*)m_window, GLFW_MOUSE_BUTTON_LEFT))
	{
		frameInputBatch.addDeviceData(DEVICE_MOUSE, BUTTON_MOUSE_LEFT);
	}
	if (glfwGetMouseButton((GLFWwindow*)m_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		frameInputBatch.addDeviceData(DEVICE_MOUSE, BUTTON_MOUSE_RIGHT);
	}
}

WindowsPlatform::WindowsPlatform() : log("WindowsPlatform"), is_win_constr(false)
{

}

WindowsPlatform::~WindowsPlatform() 
{
	delete m_platform;
	m_platform = NULL;
}

void WindowsPlatform::LoadPlatformSettings()
{
	AspectRatio aspect_ratio;
	DisplayResolution resolution;

	GetPlatformSettings(aspect_ratio, resolution);	

	SetWindowAspectRatio(aspect_ratio);
	SetWindowResolution(resolution);

#if 0
	IClearFile in_settings_file("game_settings");

	if (in_settings_file.IsOpen())
	{
		/* TODO AspectRatio - must be read from a file */
		AspectRatio aspect_ratio;
		DisplayResolution resolution;
		const char delimiter = '=';

		/* Read the whole file into memory */
		std::string settings_data(in_settings_file.Size(), ' ');
		in_settings_file.Read(&settings_data[0], in_settings_file.Size());

		/* Parse the memory buffer */
		std::stringstream data_stream(settings_data);
		std::string line;

		while (std::getline(data_stream, line))
		{
			/* Get the token */
			int delimiter_pos = line.find(delimiter);
			if (delimiter_pos == -1)
				continue;

			std::string token = line.substr(0, delimiter_pos);

			if (token == "RES_X")
			{
				resolution.x = strtol((line.substr(delimiter_pos + 1)).c_str(), NULL, 10);
			}
			else if (token == "RES_Y")
			{
				resolution.y = strtol((line.substr(delimiter_pos + 1)).c_str(), NULL, 10);
			}
			else
			{
				/* undefined token */
				continue;
			}
		}

		/* The read resolution is a valid one ? */
		if (IsValidDisplayRes(aspect_ratio, resolution))
		{
			SetWindowResolution(resolution.x, resolution.y);  //TODO here i need to pass a DisplayResolution
		}
		else
		{
			/* Load default resolution */
			SetWindowResolution(DEFAULT_WINDOWS_RES_W, DEFAULT_WINDOWS_RES_H);
		}
	}
	else
	{
		/* Load default resolution */
		SetWindowResolution(DEFAULT_WINDOWS_RES_W, DEFAULT_WINDOWS_RES_H);
	}


	/* TODO - here I have to write in game_settings */

	/* Save the settings on the disk */
	/*OClearFile out_settings_file("game_settings", io::out);

	if (out_settings_file.IsOpen())
	{
	std::string res = "RES_X=" + std::to_string(DEFAULT_WINDOWS_RES_W) + "\nRES_Y=" + std::to_string(DEFAULT_WINDOWS_RES_H);
	out_settings_file.Write(res.c_str(), res.size());
	}
	else
	{
	app_info << "[ERROR] Can't open game_settings to write." << std::endl;
	}*/
#endif
}

void WindowsPlatform::GetPlatformSettings(AspectRatio& aspect_ratio, DisplayResolution& resolution)
{
	/* Get aspect ratio */
	aspect_ratio.x = WINDOWS_ASP_RATIO_X;
	aspect_ratio.y = WINDOWS_ASP_RATIO_Y;

	/* Compute screen resolution using the multiplier value */
	resolution.width = aspect_ratio.x * WINDOWS_SCREEN_MULTIPLIER;
	resolution.height = aspect_ratio.y * WINDOWS_SCREEN_MULTIPLIER;
}

void WindowsPlatform::WindowsConstructWindow()
{
	log.message("Windows create window.", Logging::MSG_INFO);

#if(GRAPHICS_OPENGL_LATEST)
	m_window = glfwCreateWindow(m_resolution.width, m_resolution.height, "The Purge Game", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(-1);
	}
#else
	WNDCLASS   wndclass = { 0 };
	HINSTANCE  hInstance = GetModuleHandle(NULL);

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)WindowsPlatform::InitialWindowProcedure;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = "AppWindowClass";

	if (!RegisterClass(&wndclass))
		throw std::string("can't register class");

	RECT  windowRect;

	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = m_resolution.width;
	windowRect.bottom = m_resolution.height;

	DWORD wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	AdjustWindowRect(&windowRect, wStyle, false);

	m_window = CreateWindow("AppWindowClass", "3D app template", wStyle,
		(GetSystemMetrics(SM_CXSCREEN) - m_resolution.width) /*/ 2*/,
		(GetSystemMetrics(SM_CYSCREEN) - m_resolution.height) - 80/*/ 2*/, /*TODO for safety :) */
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL, NULL, hInstance, NULL);

	if (m_window == NULL)
		throw std::string("can't create app window");

	ShowWindow((HWND)m_window, true);
	UpdateWindow((HWND)m_window);
#endif
}