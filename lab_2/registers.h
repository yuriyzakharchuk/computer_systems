#ifndef REGISTERS_HEADER
#define REGISTERS_HEADER

#pragma once

#include <cstdint>
#include <cstdlib>
#include <iostream>

typedef uint64_t register_64bit;
typedef uint32_t register_32bit;

class amd64_registers
{
private:
    unsigned char *register_memory;                   
   
    register_64bit* inititalize_64_bir_register(size_t register_number) const
    {
        return (register_64bit*)(register_memory + register64_size * register_number);
    }

    register_32bit* inititalize_32_bir_register(size_t register_number) const
    {
        return (register_32bit*)(register_memory + register64_size * register_number);
    }


public:
    static const size_t common_register_count = 16,
                        register64_size = sizeof(register_64bit),
                        register32_size = sizeof(register_32bit);

    amd64_registers();
    ~amd64_registers();


    // 64-bit registers
    register_64bit *rax, *rbx, *rcx, *rdx,
                   *rsi, *rdi, *rbp, *rsp;


    // 32-bit registers
    register_32bit *eax, *ebx, *ecx, *edx,
                   *esi, *edi, *ebp, *esp;
                   
    // 32-bit floating point registers
    register_32bit *mmx1,  *mmx2,  *mmx3, *mmx4;
};

#endif //REGISTERS_HEADER