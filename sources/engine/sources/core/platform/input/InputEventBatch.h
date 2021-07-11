#pragma once
#include <vector>
#include <array>
#include "Device.h"
#include "DeviceDefinitions.h"
#include "InputEvent.h"


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
		int getDataBatchSize() const;
		const InputEvent& getDataAtIndex(int index) const;
		void addData(const InputEvent& inEvent);
		void addData(const int inDevice, const int inButton, const int inStatus);

	private:
		std::vector<InputEvent> batchData;
};