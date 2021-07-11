#include "BindingCollection.h"
#include <utility>

void BindingCollection::AddBinding(const int keyBind, const int valueBind)
{
    bindings.insert(std::unordered_map<int, int>::value_type(keyBind, valueBind));
}

void BindingCollection::DeleteBinding(const int keyBind)
{
    bindings.erase(keyBind);
}

int BindingCollection::GetBinding(const int keyBind)
{
	std::unordered_map<int, int>::iterator ite = bindings.find(keyBind);
	return (ite == bindings.end()) ? -1 : ite->second;
}

int BindingCollection::GetBinding(const InputEvent& inEvent)
{
	return GetBinding(inEvent.button);
}