#include "processor.h"

int main()
{
    processor cpu = processor();

    *cpu.registers.eax = 63;
    *cpu.registers.ebx = 7;

    cpu.div(cpu.registers.ebx);

    cpu.imul(-8, 2);
}