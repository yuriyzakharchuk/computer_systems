#include "registers.h"
#include <iostream>

class processor
{
public:
    void div(registers register)
    {
        long T remainder_quotient = 0;
        remainder_quotient |= quotient;

        for(size_t i = 0; i < sizeof(quotient) * CHAR_BIT; ++i)
        {
            remainder_quotient <<= 1;
            int8_t remainder = remainder_quotient >> CHAR_BIT;
            unsignedT difference = remainder - divisor;
            if(difference < 128)
            {
                uint16_t mask = difference;
                mask <<= CHAR_BIT;
                remainder_quotient &= mask;
                remainder_quotient |= (uint16_t)1;
            }
        }
        std::cout << "Remainder: " << (int)(remainder_quotient >> CHAR_BIT) << std::endl
                << "Result: " << (int)(remainder_quotient & 255) << std::endl;
    }
    amd64_registers registers;
};