#include "InputEventBatch.h"

InputEventBatch::InputEventBatch()
{
	for(int i=0; i < batchDataOfSupportedDevices.size(); ++i)
	{
		// We allocate memory but the size remains the same
		batchDataOfSupportedDevices[i].reserve(INPUT_EVENT_BATCH_MAX_SIZE);
	}
}

bool InputEventBatch::isEmpty()
{
	for(int i=0; i < batchDataOfSupportedDevices.size(); ++i)
	{
		if(batchDataOfSupportedDevices[i].size())
			return false;
	}

	return true;
}

int InputEventBatch::getDeviceBatchSize(int device) const
{
	return batchDataOfSupportedDevices[device].size();
}

int InputEventBatch::getDeviceDataAtIndex(int device, int index) const 
{
	return batchDataOfSupportedDevices[device][index];
}

void InputEventBatch::addDeviceData(int device, int data)
{
	if(batchDataOfSupportedDevices[device].size() < INPUT_EVENT_BATCH_MAX_SIZE)
		batchDataOfSupportedDevices[device].push_back(data);
}