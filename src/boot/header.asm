bits 32

MAG equ 0x1BADB002
FLG equ 0x00
CHK equ -(MAG + FLG)

section .multiboot
        align 4
        dd MAG
        dd FLG
        dd CHK