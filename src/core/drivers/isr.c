#include "../inc/isr.h"
#include "../inc/idt.h"
#include "../inc/io.h"
#include "../inc/stdio.h"

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

const char *exception_messages[32] = {
    "Division By Zero",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved"
};

static isr_t isr_handlers[32];
static irq_t irq_handlers[16];

void isrRegisterHandler(uchar n, isr_t handler) {
    if (n < 32) isr_handlers[n] = handler;
}

void irqRegisterHandler(uchar irq, irq_t handler) {
    if (irq < 16) irq_handlers[irq] = handler;
}

static void pic_remap(void) {
    uchar mask1 = inb(PIC1_DATA);
    uchar mask2 = inb(PIC2_DATA);

    outb(PIC1_CMD,  0x11); io_wait();
    outb(PIC2_CMD,  0x11); io_wait();
    outb(PIC1_DATA, 0x20); io_wait();
    outb(PIC2_DATA, 0x28); io_wait();
    outb(PIC1_DATA, 0x04); io_wait();
    outb(PIC2_DATA, 0x02); io_wait();
    outb(PIC1_DATA, 0x01); io_wait();
    outb(PIC2_DATA, 0x01); io_wait();

    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

extern uint isr_stub_table[32];
extern uint irq_stub_table[16];

void isrInit(void) {
    idtInit();
    pic_remap();

    for (int i = 0; i < 32; i++)
        setIdtGate(i,      isr_stub_table[i], 0x08, 0x8E);

    for (int i = 0; i < 16; i++)
        setIdtGate(i + 32, irq_stub_table[i], 0x08, 0x8E);

    printf("ISR: %COK%C\n", GREEN, WHITE);
}

void isr_handler(registers_t *regs) {
    if (regs->int_no < 32 && isr_handlers[regs->int_no]) {
        isr_handlers[regs->int_no](regs);
    } else {
        setcolor(BLACK, RED);
        printf("Unhandled exception %d (%s)  err=0x%x\n",
               regs->int_no,
               exception_messages[regs->int_no],
               regs->err_code);
        __asm__ volatile ("cli; hlt");
    }
}

void irq_handler(registers_t *regs) {
    if (regs->int_no >= 40) outb(PIC2_CMD, PIC_EOI);
    outb(PIC1_CMD, PIC_EOI);

    uchar irq_no = (uchar)(regs->int_no - 32);
    if (irq_no < 16 && irq_handlers[irq_no])
        irq_handlers[irq_no](regs);
}