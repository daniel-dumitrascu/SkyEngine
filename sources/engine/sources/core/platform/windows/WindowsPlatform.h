#ifndef WINDOWSPLATFOM
#define WINDOWSPLATFOM

#include <windows.h>
#include <vector>
#include <map>
#include <iostream>
#include "../Platform.h"
#include "../input/Device.h"
#include "../../logging/Logging.h"

class InputEventBatch;

class WindowsPlatform : public Platform
{
	public:

		static Platform* GetPlatformHandle();

		void InitPlatform(void** screen_handle);
		void UpdatePlatform();
		bool IsRunning();

	private:

		WindowsPlatform();
		WindowsPlatform(const WindowsPlatform& copy) = delete;
		~WindowsPlatform();

		WindowsPlatform& operator=(WindowsPlatform& copy) = delete;

		void LoadPlatformSettings();
		void GetPlatformSettings(AspectRatio& aspect_ratio, DisplayResolution& resolution);
		void WindowsConstructWindow();
		void CheckInput();
		void checkKeyInput(InputEventBatch& frameInputBatch);
		void checkMouseInput(InputEventBatch& frameInputBatch);

	private:

		Logging log;
		bool is_win_constr;
		std::vector<void (WindowsPlatform::*)(InputEventBatch& frameInputBatch)> platformAvailableInputDevices;
};

#endif