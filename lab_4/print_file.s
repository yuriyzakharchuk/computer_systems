.section .text

.global _start

_start:    
    movq (%rsp), %rax       /* argc to RAX                                  */
    cmp $2, %eax            /* subrt 1 and check if zero                    */
    jne argument_error      /* call number of open() in RAX                 */    
                            /* --- call open() ---                          */
    movq 16(%rsp), %rdi     /* 1 - in RDI - pointer to char*                */
    syscall
    push %rax               /* file descriptor to stack                     */

    mov $8, %eax            /* --- call lseek() ---                         */
    movq (%rsp), %rdi       /* 1 - file descriptor in sack                  */
    xor %esi, %esi          /* 2 - SEEK_END                                 */
    mov $2, %edx
    syscall
    movq %rax, %rsi         /* len to RSI                                   */

    mov $9, %eax            /* --- call mmap() ---                          */
    xor %edi, %edi          /* 1 - NULL                                     */
    dec %edx                /* 3 - PROT_READ                                */
    inc %r10d               /* 4 - MAP_SHARED                               */
    movq (%rsp), %r8        /* 5 - file descriptor from stackhead           */
    xor %r9d, %r9d          /* 6 - 0                                        */
    syscall        
    movq %rax, %r12         /* memptr to R12                                */
    
    mov $1, %eax            /* --- call write() ---                         */
    inc %edi                /* 1 - stdout                                   */
    movq %rsi, %rdx         /* 3 - len                                      */
    movq %r12, %rsi         /* 2 - memptr                                   */
    syscall                 /* ignoring returned value to simplify          */
                            
    mov $11, %eax           /* --- call munmap() ---                        */
    mov %rsi, %rdi          /* 1 - memptr                                   */
    mov %rdx, %rsi          /* 2 - len                                      */
    syscall                 /* ignoring returned value to sipmlify          */    
    
    mov $60, %eax
    xor %edi, %edi          /* 1 - exit code                                */
    syscall

argument_error:
    mov $60, %eax
    mov $1, %edi
    syscall
