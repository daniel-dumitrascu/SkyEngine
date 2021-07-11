#ifndef DEVICE_BINDING
#define DEVICE_BINDING

#include <iostream>
#include <unordered_map>
#include "platform/input/InputEvent.h"

class BindingCollection
{
    public:
        void AddBinding(const int keyBind, const int valueBind);
        void DeleteBinding(const int keyBind);
        int GetBinding(const int keyBind);
        int GetBinding(const InputEvent& inEvent);
    private:
        std::unordered_map<int, int> bindings;
};

#endif