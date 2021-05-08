#ifndef BINARY_ARRAY
#define BINARY_ARRAY

#include <vector>

class BinaryArray
{
    public:
        BinaryArray(unsigned int size);
        ~BinaryArray() {};

        bool IsFlagON(unsigned int pos);
		void SetFlagON(unsigned int pos);
		void SetFlagOFF(unsigned int pos);

    private:
        std::vector<bool> data;      
};

#endif