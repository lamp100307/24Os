#include "../inc/pit.h"
#include "../inc/isr.h"
#include "../inc/io.h"
#include "../inc/stdio.h"

static volatile uint pit_ticks = 0;

uint pitGetTicks(void) {
    return pit_ticks;
}

void pitSleep(uint ms) {
    uint start = pit_ticks;
    while ((pit_ticks - start) < ms)
        __asm__ volatile ("hlt");
}

static void pit_irq_handler(registers_t *regs) {
    (void)regs;
    pit_ticks++;
}

void pitInit(uint freq) {
    uint div = 1193180 / freq;

    outb(0x43, 0x36);
    outb(0x40, (uchar)(div & 0xFF));
    outb(0x40, (uchar)((div >> 8) & 0xFF));

    irqRegisterHandler(0, pit_irq_handler);

    printf("PIT: %COK%C  (%d Hz)\n", GREEN, WHITE, freq);
}