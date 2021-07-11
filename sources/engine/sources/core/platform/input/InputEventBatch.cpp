#include "InputEventBatch.h"

InputEventBatch::InputEventBatch()
{
	// We allocate memory but the size remains the same
	batchData.reserve(INPUT_EVENT_BATCH_MAX_SIZE);
}

bool InputEventBatch::isEmpty()
{
	return batchData.size() == 0 ? true : false;
}

int InputEventBatch::getDataBatchSize() const
{
	return batchData.size();
}

const InputEvent& InputEventBatch::getDataAtIndex(int index) const 
{
	return batchData[index];
}

void InputEventBatch::addData(const InputEvent& inEvent)
{
	batchData.push_back(inEvent);
}

void InputEventBatch::addData(const int inDevice, const int inButton, const int inStatus)
{
	InputEvent ev(inDevice, inButton, inStatus);
	addData(ev);
}

