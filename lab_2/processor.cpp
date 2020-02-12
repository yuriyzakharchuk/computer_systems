#include "processor.h"

// Divides unsigned the value in the EAX register (dividend) by the source operand
// (divisor) and stores the result in the EDX:EAX registers. 

void processor::div(const register_32bit *const divisor)
{
    assert(divisor != this->registers.eax);
    std::cout << "\n\t\tDIV " << *this->registers.eax << " " << *divisor << std::endl;
    

    register_32bit* rax_sign_bits = ((register_32bit*)this->registers.rax) + 1;
    
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
    std::cout << "EAX (result): " << *this->registers.eax << "     " 
              << std::bitset<32>(*this->registers.eax) << std::endl;
    std::cout << "EDX (remainder):" << *this->registers.edx << "     "
              << std::bitset<32>(*this->registers.edx) << std::endl;
}



void processor::arithmetic_shift(std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &bitmap) const
{
    auto tmp = (uint8_t)bitmap[65];
    bitmap >>= 1;
    bitmap[65] = tmp;
}



bool processor::full_adder(bool b1, bool b2, bool& carry) const
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}



void processor::add(std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &x,
    const std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> &y) const
{
    bool carry = false;
    for (size_t i = 0; i < x.size(); i++)    
    {
        x[i] = full_adder(x[i], y[i], carry);
    }
}



void processor::imul(int32_t multiplier, int32_t multiplicand)
{
    std::cout << "\n\t\tIMUL " << multiplier << " " << multiplicand << std::endl;

    std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> A = multiplier;
    std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> S = -multiplier;
    std::bitset<sizeof(register_64bit) * CHAR_BIT + 2> P = multiplicand;
    A <<= sizeof(register_32bit) * CHAR_BIT + 1;
    S <<= sizeof(register_32bit) * CHAR_BIT + 1;
    P <<= 1;

    for(size_t i = 0; i < sizeof(register_32bit) * CHAR_BIT; ++i)
    {
        std::cout << "----------------------------------------------------"
                     "-------------------------"
                     << std::endl;
        std::cout << "A:\t   " << A << std::endl;
        std::cout << "S:\t   " << S << std::endl;
        std::cout << "P:\t   " << P << std::endl;

        switch((uint8_t)P[0] | (uint8_t)P[1] << 1)
        {
            case 0b01:
            {
                std::cout << "\nP + A:\t   " << P << std::endl
                          << "\t+  " << A << std::endl;
                add(P, A);
                std::cout << "\t   " << P << std::endl << std::endl;
                break;
            }
            case 0b10:
            {
                std::cout << "\nP + S:\t   " << P << std::endl
                          << "\t+  " << S << std::endl;
                add(P, S);
                std::cout << "\t   " << P << std::endl << std::endl;
                break;
            }
        }
        arithmetic_shift(P);
        std::cout << "Shifted P: " << P << std::endl;
    }
    P >>= 1;
    
    *this->registers.rax = 0;
    for(size_t i = 0; i < sizeof(register_64bit) * CHAR_BIT; ++i)
    {
        register_64bit bit = (bool)P[i];
        *this->registers.rax |= (bit << i);
    }

    std::cout << "\nResult: " << static_cast<int64_t>(*this->registers.rax) << std::endl
              << std::bitset<sizeof(register_64bit) * CHAR_BIT>(*this->registers.rax) << std::endl;
}

//only for 32-bit floating point numbers
void processor::mul_fp(register_32bit *multiplicand)
{
    assert(this->registers.mmx1 != multiplicand);
    std::cout << "\n\t\tFLOATING POINT MUL " << std::endl
              << *reinterpret_cast<float*>(this->registers.mmx1) << "\t  "  
              << std::bitset<sizeof(register_32bit) * CHAR_BIT>(*this->registers.mmx1) << std::endl
              << *reinterpret_cast<float*>(multiplicand) << "\t  "
              << std::bitset<sizeof(register_32bit) * CHAR_BIT>(*multiplicand) << std::endl;

    if(*this->registers.mmx1 == 0 || *multiplicand == 0)
    {
        *this->registers.mmx1 = 0;
        return;
    }

	register_32bit multiplier_mantissa = *this->registers.mmx1 & 0x007FFFFF + 0x800000;
	register_32bit multiplicand_mantissa = *multiplicand & 0x007FFFFF + 0x800000;

    register_32bit sign = (*this->registers.mmx1 >> 31) & 0b01 ^ (*multiplicand  >> 31) & 0b01;
    register_32bit exp = ((*this->registers.mmx1 >> 23) & 0b011111111) + ((*multiplicand  >> 23) & 0b011111111) - 127;

    multiplier_mantissa = (multiplier_mantissa | 0x00800000) << 7;
	multiplicand_mantissa = (multiplicand_mantissa | 0x00800000) << 8;

	register_64bit mantissa = (register_64bit)multiplier_mantissa * (register_64bit)multiplicand_mantissa;
    
    //shift most significatn bit to right 
	for(size_t i = 22; (mantissa & ((uint64_t)1 << 63)) / ((uint64_t)1 << 63) == 0 && (i != 0); --i)
    {
        mantissa <<= 1;
    }
    mantissa <<= 1;
	mantissa >>= 41;

    std::cout << "Sing: " << sign << std::endl
              << "Exp: "  << exp << std::endl
              << "Mantissa: " << std::bitset<64>(mantissa) << std::endl;

    *this->registers.mmx1 |= sign << 31;
    *this->registers.mmx1 |= exp << 23;
    *this->registers.mmx1 |= mantissa;

    std::cout << "Result: " << std::fixed << *reinterpret_cast<float*>(this->registers.mmx1) << "\t" 
              << std::bitset<sizeof(register_32bit) * CHAR_BIT>(*this->registers.mmx1) << std::endl;
}