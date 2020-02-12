#include "processor.h"
#include <iostream>

int main()
{
    processor cpu = processor();
    *cpu.registers.mmx1 = 0b01000000001000000000000000000000;
    *cpu.registers.mmx2 = 0b01000000100000000000000000000000;
    cpu.mul_fp(cpu.registers.mmx2);

    *cpu.registers.eax = 63;
    *cpu.registers.ebx = 7;

    cpu.div(cpu.registers.ebx);

    cpu.imul(-8, 2);
}