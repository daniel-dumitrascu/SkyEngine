#include "BinaryArray.h"
#include <iostream>


BinaryArray::BinaryArray(unsigned int size)
{
    int flagCount = 0;
    if(size == 0)
    {
        std::cout << "[WARN] Input size was zero, we default to 32 bit flags" << std::endl;
        flagCount = 32;
    }
    else 
    {
        flagCount = size;
    }

    data.resize(flagCount);

    // Reseting the flags
    for(int i=0; i < data.size(); ++i)
        data[i] = false;
}

bool BinaryArray::IsFlagON(unsigned int pos)
{
    if(pos >= 0 && pos < data.size())
    {
        return data[pos];
    }

    std::cout << "[WARN]BinaryArray::IsFlagON: The provided index [" << pos << "] is out of [0-" << data.size()-1 << "] range" << std::endl;
    return false;
}

void BinaryArray::SetFlagON(unsigned int pos)
{
    if(pos >= 0 && pos < data.size())
    {
        data[pos] = true;
    }
}

void BinaryArray::SetFlagOFF(unsigned int pos)
{
    if(pos >= 0 && pos < data.size())
    {
        data[pos] = false;
    }
}