#ifndef DEVICE_BINDING
#define DEVICE_BINDING

#include <iostream>
#include <unordered_map>
#include <memory>
#include "platform/input/InputEvent.h"

struct DataBindingWrapper
{
	DataBindingWrapper(const int action, std::shared_ptr<void> extraData)
	{
		this->action = action;
		this->extraData = std::move(extraData);
	}

	int action;

	// We used a shared_ptr because this is
	// the only one that could hold a void*
	std::shared_ptr<void> extraData; 
};

class BindingCollection
{
    public:
        void AddBinding(const int keyBind, const int valueBind, std::shared_ptr<void> extraData=nullptr);
        void DeleteBinding(const int keyBind);
		const DataBindingWrapper* GetBinding(const int keyBind);
		const DataBindingWrapper* GetBinding(const InputEvent& inEvent);
    private:
        std::unordered_map<int, DataBindingWrapper> bindings;
};

#endif