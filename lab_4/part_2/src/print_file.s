.section .text

.global _start

_start:    
    movq (%rsp), %rax       /* argc to RAX                                  */
    cmp $2, %eax            /* check if zero                                */
    jne exit                /* call number of open() - 2 in RAX             */    
                            /* --- call open() ---                          */
    movq 16(%rsp), %rdi     /* 1 - in RDI - pointer to char*                */
    syscall
    push %rax               /* file descriptor to stack                     */

    mov $8, %eax            /* --- call lseek() ---                         */
    movq (%rsp), %rdi       /* 1 - file descriptor on stack                 */
    xor %esi, %esi          /* 2 - offset = 0                               */
    mov $2, %edx            /* 3 - whence = SEEK_END (2)                    */
    syscall
    movq %rax, %rsi         /* len to RSI                                   */

    mov $9, %eax            /* --- call mmap() ---                          */
    xor %edi, %edi          /* 1 - addr = NULL                              */
    dec %edx                /* 3 - prot = PROT_READ                         */
    inc %r10d               /* 4 - flags = MAP_SHARED                       */
    movq (%rsp), %r8        /* 5 - file descriptor from stackhead           */
    xor %r9d, %r9d          /* 6 - offset = 0                               */
    syscall        
    movq %rax, %r12         /* memptr to R12                                */
    
    mov $1, %eax            /* --- call write() ---                         */
    inc %edi                /* 1 - fd = stdout                              */
    movq %rsi, %rdx         /* 3 - count = len                              */
    movq %r12, %rsi         /* 2 - buf = memptr                             */
    syscall                 /* ignoring ret. value to simplify              */
                            
    mov $11, %eax           /* --- call munmap() ---                        */
    mov %rsi, %rdi          /* 1 - addr = memptr                            */
    mov %rdx, %rsi          /* 2 - length = len                             */
    syscall                 /* ignoring ret. value to sipmlify              */    
    
exit:
    mov $60, %eax           /* --- call exit() ---                          */
    xor %edi, %edi          /* 1 - status = 0 (exit code)                   */
    syscall

