#pragma once
#include <vector>
#include <array>
#include "Device.h"
#include "DeviceDefinitions.h"


// This defines the max number of keys 
// stored and procesed at each frame
const int INPUT_EVENT_BATCH_MAX_SIZE = 10;

// InputEventBatch can store input data from all the  
// supported devices that gave input data at a given frame
struct InputEventBatch
{
	public:
		InputEventBatch();
		~InputEventBatch() {};

		bool isEmpty();
		int getDeviceBatchSize(int device) const;
		int getDeviceDataAtIndex(int device, int index) const;
		void addDeviceData(int device, int data);

	private:
		std::array<std::vector<int>, DEVICE_COUNT> batchDataOfSupportedDevices;
};