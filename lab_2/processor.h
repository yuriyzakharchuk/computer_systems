#ifndef PROCESSOR_HEADER
#define PROCESSOR_HEADER

#include "registers.h"
#include <iostream>
#include <climits>
#include <bitset>
#include <cassert>

class processor
{
public:
    void div(const register_32bit*);

    amd64_registers registers;
};

#endif //PROCESSOR_HEADER