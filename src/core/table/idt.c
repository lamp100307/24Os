#include "idt.h"
#include "stdio.h"

static struct IDTE idt[256];
static struct IDTP idt_ptr;

extern void idtflush(uint32_t);
extern void irq0_handler();

void setIdtGate(int n, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[n].base_low = base & 0xFFFF;
    idt[n].base_high = (base >> 16) & 0xFFFF;
    idt[n].sel = sel;
    idt[n].zero = 0;
    idt[n].flags = flags;
}

void idtInit() {
    idt_ptr.limit = sizeof(struct IDTE) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt;
    idtflush((uint32_t)&idt_ptr);
    printf("IDT: %COK%C\n", GREEN, WHITE);
}