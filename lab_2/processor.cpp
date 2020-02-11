#include "processor.h"

// Divides unsigned the value in the EDX:EAX registers (dividend) by the source operand
// (divisor) and stores the result in the EDX:EAX registers. 

void processor::div(const register_32bit *const divisor)
{
    assert(divisor != this->registers.eax);
    assert(divisor != this->registers.edx);

    register_32bit* rax_sign_bits = ((register_32bit*)this->registers.rax) + 1;
    *rax_sign_bits = *this->registers.edx;
    
    for(size_t i = 0; i < sizeof(register_32bit) * CHAR_BIT; ++i)
    {
        *this->registers.rax <<= 1;
        register_32bit difference = *rax_sign_bits - *divisor;

        std::cout << "Step " << i << " - RAX: " << std::bitset<sizeof(register_64bit) * CHAR_BIT>(*this->registers.rax)
                  << " Diff: " << std::bitset<sizeof(register_32bit) * CHAR_BIT>(difference) << std::endl;

        if(!(difference & (1 << 31)))
        {
            *rax_sign_bits = difference;
            *this->registers.eax |= 1;
            std::cout << "          RAX: " << std::bitset<sizeof(register_64bit) * CHAR_BIT>(*this->registers.rax)
                      << " Diff: " << std::bitset<sizeof(register_32bit) * CHAR_BIT>(difference) << std::endl;
        }
        std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
    }
    *this->registers.edx = *rax_sign_bits;
    std::cout << "EAX: " << *this->registers.eax << "     " << std::bitset<32>(*this->registers.eax) << std::endl;
    std::cout << "EDX: " << *this->registers.edx << "     " << std::bitset<32>(*this->registers.edx) << std::endl;
}


void processor::arithmetic_shift(std::bitset<66> &bitmap)
{
    auto tmp = bitmap[65];
    bitmap >>= 1;
    bitmap[65] = tmp;
}

bool processor::full_adder(bool b1, bool b2, bool& carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}

void processor::add(std::bitset<66> &x, const std::bitset<66> &y)
{
    bool carry = false;
    for (size_t i = 0; i < x.size(); i++)    
    {
        x[i] = full_adder(x[i], y[i], carry);
    }
}

void processor::imul(int32_t multiplier, int32_t multiplicand)
{
    std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> A = multiplier;
    std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> S = -multiplier;
    std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> P = multiplicand;
    A <<= sizeof(register_32bit) * CHAR_BIT + 1;
    S <<= sizeof(register_32bit) * CHAR_BIT + 1;
    P <<= 1;

    for(size_t i = 0; i < sizeof(register_32bit) * CHAR_BIT; ++i)
    {
        std::cout << "---------------------------------------------------------------------" << std::endl;
        switch((uint8_t)P[0] | (uint8_t)P[1] << 1)
        {
            case 0b01:
            {
                add(P, A);
                break;
            }
            case 0b10:
            {
                add(P, S);
                break;
            }
        }
        std::cout << "A: " << A << std::endl;
        std::cout << "S: " << S << std::endl;
        std::cout << "P: " << P << std::endl;
        arithmetic_shift(P);
    }
    P[65] = 0;
    P >>= 1;
    std::cout << "R: " << P << std::endl;
}