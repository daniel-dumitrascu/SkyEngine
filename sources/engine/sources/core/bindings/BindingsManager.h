#ifndef DEVICE_TO_ACTIONS
#define DEVICE_TO_ACTIONS

#include "BindingCollection.h"
#include <unordered_map>
#include <vector>
#include <memory>

class BindingsManager
{
    public:
        static BindingsManager& GetInstance();
        BindingCollection* GetLayerBinding(int layer);

    private:
		BindingsManager();
		~BindingsManager() = default;
		BindingsManager(const BindingsManager& copy) = delete;
		BindingsManager& operator=(const BindingsManager& copy) = delete;
        void ConstructBindings();
        
    private:

		std::unordered_map<int, std::unique_ptr<BindingCollection>> bindingsForDifferentLayers;
};

#endif