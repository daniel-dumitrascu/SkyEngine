#include "BindingCollection.h"
#include <utility>

void BindingCollection::AddBinding(int keyBind, int valueBind)
{
    bindings.insert(std::unordered_map<int, int>::value_type(keyBind, valueBind));
}

void BindingCollection::DeleteBinding(int keyBind)
{
    bindings.erase(keyBind);
}

int BindingCollection::GetBinding(int keyBind)
{
    std::unordered_map<int, int>::iterator ite = bindings.find(keyBind);
    return (ite == bindings.end()) ? -1 : ite->second;
}