#include "registers.h"

amd64_registers::amd64_registers() : 
    register_memory(new unsigned char[register64_size * common_register_count]),

    //64-bit registers
    rax (inititalize_64_bir_register(0)),
    rbx (inititalize_64_bir_register(1)),
    rcx (inititalize_64_bir_register(2)),
    rdx (inititalize_64_bir_register(3)),

    rsi (inititalize_64_bir_register(4)),
    rdi (inititalize_64_bir_register(5)),
    rbp (inititalize_64_bir_register(6)),
    rsp (inititalize_64_bir_register(7)),

    // 64-bit floating point registers
    mmx1 (inititalize_64_bir_register(8)),
    mmx2 (inititalize_64_bir_register(9)),
    mmx3 (inititalize_64_bir_register(10)),
    mmx4 (inititalize_64_bir_register(11)),

    //32-bit registers
    eax (inititalize_32_bir_register(0)),
    ebx (inititalize_32_bir_register(1)),
    ecx (inititalize_32_bir_register(2)),
    edx (inititalize_32_bir_register(3)),

    esi (inititalize_32_bir_register(4)),
    edi (inititalize_32_bir_register(5)),
    ebp (inititalize_32_bir_register(6)),
    esp (inititalize_32_bir_register(7))   
{}

amd64_registers::~amd64_registers()
{
    delete[] register_memory;
}