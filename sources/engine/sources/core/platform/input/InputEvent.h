#pragma once
#include "DeviceDefinitions.h"

struct InputEvent
{
	InputEvent(int inDevice, int inButton, int inStatus)
	{
		device = inDevice;
		button = inButton;
		status = inStatus;
	}

	int device;
	int button;
	int status;
};