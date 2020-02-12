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
    void mul_fp(const register_64bit*);

private:
    bool full_adder(bool b1, bool b2, bool& carry) const;
    void arithmetic_shift(std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &bitmap) const;
    void add(std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &x,
         const std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &y) const;
};

#endif //PROCESSOR_HEADER