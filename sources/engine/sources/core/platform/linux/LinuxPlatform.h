#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "../Platform.h"
#include "../input/Device.h"
#include "../../logging/Logging.h"

class InputEventBatch;

class LinuxPlatform : public Platform
{
    public:

		static Platform* GetPlatformHandle();

		void InitPlatform(void** screen_handle);
		void UpdatePlatform();
		bool IsRunning();
	
	private:

		LinuxPlatform();
		LinuxPlatform(const LinuxPlatform& copy) = delete;
		~LinuxPlatform();

		LinuxPlatform& operator=(LinuxPlatform& copy) = delete;

		void LoadPlatformSettings();
		void GetPlatformSettings(AspectRatio& aspect_ratio, DisplayResolution& resolution);
		void LinuxConstructWindow();	
		void CheckInput();
		void checkKeyInput(InputEventBatch& frameInputBatch);
		void checkMouseInput(InputEventBatch& frameInputBatch);

	private:

		Logging log;
		bool is_win_constr;
		std::vector<void (LinuxPlatform::*)(InputEventBatch& frameInputBatch)> platformAvailableInputDevices;
};