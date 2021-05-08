#ifndef DEVICE_H
#define DEVICE_H

#include "../../utils/BinaryArray.h"

struct Device
{
	Device(int buttonCount) : m_keys_status(buttonCount)
	{}

	BinaryArray m_keys_status; 	// This is telling us if the key is pressed or not
};


#endif