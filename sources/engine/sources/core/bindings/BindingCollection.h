#ifndef DEVICE_BINDING
#define DEVICE_BINDING

#include <iostream>
#include <unordered_map>

class BindingCollection
{
    public:
        void AddBinding(int keyBind, int valueBind);
        void DeleteBinding(int keyBind);
        int GetBinding(int keyBind);
    private:
        std::unordered_map<int, int> bindings;
};

#endif