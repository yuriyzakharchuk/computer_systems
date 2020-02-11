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

    r8  (inititalize_64_bir_register(8)),
    r9  (inititalize_64_bir_register(9)),
    r10 (inititalize_64_bir_register(10)),
    r11 (inititalize_64_bir_register(11)),
    r12 (inititalize_64_bir_register(12)),
    r13 (inititalize_64_bir_register(3)),
    r14 (inititalize_64_bir_register(14)),
    r15 (inititalize_64_bir_register(15)),

    //32-bit registers
    eax (inititalize_32_bir_register(0)),
    ebx (inititalize_32_bir_register(1)),
    ecx (inititalize_32_bir_register(2)),
    edx (inititalize_32_bir_register(3)),

    esi (inititalize_32_bir_register(4)),
    edi (inititalize_32_bir_register(5)),
    ebp (inititalize_32_bir_register(6)),
    esp (inititalize_32_bir_register(7)),

    r8d  (inititalize_32_bir_register(8)),
    r9d  (inititalize_32_bir_register(9)),
    r10d (inititalize_32_bir_register(10)),
    r11d (inititalize_32_bir_register(11)),
    r12d (inititalize_32_bir_register(12)),
    r13d (inititalize_32_bir_register(3)),
    r14d (inititalize_32_bir_register(14)),
    r15d (inititalize_32_bir_register(15))    
{}

amd64_registers::~amd64_registers()
{
    delete[] register_memory;
}