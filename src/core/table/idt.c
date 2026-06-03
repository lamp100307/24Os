#include "../inc/idt.h"
#include "../inc/stdio.h"

static struct IDTE idt[256];
static struct IDTP idt_ptr;

extern void idtflush(uint);
extern void irq0_handler();

void setIdtGate(int n, uint base, ushort sel, uchar flags) {
    idt[n].base_low = base & 0xFFFF;
    idt[n].base_high = (base >> 16) & 0xFFFF;
    idt[n].sel = sel;
    idt[n].zero = 0;
    idt[n].flags = flags;
}

void idtInit() {
    idt_ptr.limit = sizeof(struct IDTE) * 256 - 1;
    idt_ptr.base = (uint)&idt;
    idtflush((uint)&idt_ptr);
    printf("IDT: %COK%C\n", GREEN, WHITE);
}