global gdtflush
global idtflush

%macro ISR_NOERR 1
global isr%1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

%macro IRQ 2
global irq%1
irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

ISR_NOERR  0   ; Divide-by-zero
ISR_NOERR  1   ; Debug
ISR_NOERR  2   ; NMI
ISR_NOERR  3   ; Breakpoint
ISR_NOERR  4   ; Overflow
ISR_NOERR  5   ; Bound Range Exceeded
ISR_NOERR  6   ; Invalid Opcode
ISR_NOERR  7   ; Device Not Available
ISR_ERR    8   ; Double Fault
ISR_NOERR  9   ; Coprocessor Segment Overrun
ISR_ERR   10   ; Invalid TSS
ISR_ERR   11   ; Segment Not Present
ISR_ERR   12   ; Stack-Segment Fault
ISR_ERR   13   ; General Protection Fault
ISR_ERR   14   ; Page Fault
ISR_NOERR 15   ; Reserved
ISR_NOERR 16   ; x87 FPU Error
ISR_ERR   17   ; Alignment Check
ISR_NOERR 18   ; Machine Check
ISR_NOERR 19   ; SIMD Floating-Point Exception
ISR_NOERR 20   ; Virtualization Exception
ISR_NOERR 21   ; Reserved
ISR_NOERR 22   ; Reserved
ISR_NOERR 23   ; Reserved
ISR_NOERR 24   ; Reserved
ISR_NOERR 25   ; Reserved
ISR_NOERR 26   ; Reserved
ISR_NOERR 27   ; Reserved
ISR_NOERR 28   ; Reserved
ISR_NOERR 29   ; Reserved
ISR_ERR   30   ; Security Exception
ISR_NOERR 31   ; Reserved
IRQ  0, 32   ; PIT timer
IRQ  1, 33   ; Keyboard
IRQ  2, 34   ; Cascade
IRQ  3, 35   ; COM2
IRQ  4, 36   ; COM1
IRQ  5, 37   ; LPT2
IRQ  6, 38   ; Floppy
IRQ  7, 39   ; LPT1 / spurious
IRQ  8, 40   ; CMOS RTC
IRQ  9, 41   ; Free / ACPI
IRQ 10, 42   ; Free
IRQ 11, 43   ; Free
IRQ 12, 44   ; PS/2 Mouse
IRQ 13, 45   ; FPU / Coprocessor
IRQ 14, 46   ; Primary ATA
IRQ 15, 47   ; Secondary ATA

gdtflush:
    mov eax, [esp + 4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret

idtflush:
    mov eax, [esp + 4]
    lidt [eax]
    ret

extern isr_handler
isr_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call isr_handler
    add esp, 4
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret

extern irq_handler
irq_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    call irq_handler
    add esp, 4
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret

section .data
global isr_stub_table
isr_stub_table:
    dd isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7
    dd isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15
    dd isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23
    dd isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31

global irq_stub_table
irq_stub_table:
    dd irq0,  irq1,  irq2,  irq3,  irq4,  irq5,  irq6,  irq7
    dd irq8,  irq9,  irq10, irq11, irq12, irq13, irq14, irq15