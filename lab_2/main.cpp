#include "processor.h"

int main()
{
    processor cpu = processor();

    *cpu.registers.eax = 0b11;
    *cpu.registers.edx = 1;
    *cpu.registers.ebx = 0b101;
    cpu.div(cpu.registers.ebx);
}