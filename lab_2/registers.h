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
    
    //flag register and istruction pointer
    register_64bit *rflags = (register_64bit*)(register_memory + register64_size * (common_register_count - 2)),
                   *rip    = (register_64bit*)(register_memory + register64_size * (common_register_count - 1));
                   
   
    register_64bit* inititalize_64_bir_register(size_t register_number) const
    {
        return (register_64bit*)(register_memory + register64_size * register_number);
    }

    register_32bit* inititalize_32_bir_register(size_t register_number) const
    {
        return (register_32bit*)(register_memory + register64_size * register_number);
    }


public:
    static const size_t common_register_count = 18,
                        register64_size = sizeof(register_64bit),
                        register32_size = sizeof(register_32bit);

    amd64_registers();
    ~amd64_registers();


    //64-bit registers
    register_64bit *rax, *rbx, *rcx, *rdx,
                   *rsi, *rdi, *rbp, *rsp,

                   *r8,  *r9,  *r10, *r11,
                   *r12, *r13, *r14, *r15;

    //32-bit registers
    register_32bit *eax, *ebx, *ecx, *edx,
                   *esi, *edi, *ebp, *esp,

                   *r8d,  *r9d,  *r10d, *r11d,
                   *r12d, *r13d, *r14d, *r15d;
};

#endif //REGISTERS_HEADER