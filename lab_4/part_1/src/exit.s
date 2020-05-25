.include "defs.h"

.section .text
.global _start

_start:
	movq $SYS_EXIT, %rax
	movq $0, %rdi
	syscall

