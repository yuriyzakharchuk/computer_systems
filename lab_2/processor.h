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
    amd64_registers registers;

    void div(const register_32bit*);
    void imul(int32_t, int32_t);

private:
    bool full_adder(bool b1, bool b2, bool& carry);
    void arithmetic_shift(std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &bitmap);
    void add(std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &x, const std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &y);
};

#endif //PROCESSOR_HEADER