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