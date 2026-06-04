bits 32
global _start
extern kentry

section .text
_start:
        cli
        mov esp, stack
        push ebx
        push eax
        call kentry
.loop:
        hlt
        jmp .loop

section .bss
align 16
resb 16384
stack: