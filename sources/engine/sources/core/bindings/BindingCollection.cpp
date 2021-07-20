#include "BindingCollection.h"
#include <utility>

void BindingCollection::AddBinding(const int keyBind, const int valueBind, std::shared_ptr<void> extraData)
{
	DataBindingWrapper wrapper(valueBind, extraData);
    bindings.insert(std::unordered_map<int, DataBindingWrapper>::value_type(keyBind, wrapper));
}

void BindingCollection::DeleteBinding(const int keyBind)
{
    bindings.erase(keyBind);
}

const DataBindingWrapper* BindingCollection::GetBinding(const int keyBind)
{
	std::unordered_map<int, DataBindingWrapper>::iterator ite = bindings.find(keyBind);
	return (ite == bindings.end()) ? nullptr : &(ite->second);
}

const DataBindingWrapper* BindingCollection::GetBinding(const InputEvent& inEvent)
{
	return GetBinding(inEvent.button);
}