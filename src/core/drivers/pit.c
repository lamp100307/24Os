#include "pit.h"
#include "isr.h"
#include "io.h"
#include "stdio.h"

static volatile uint32_t pit_ticks = 0;

uint32_t pitGetTicks(void) {
    return pit_ticks;
}

void pitSleep(uint32_t ms) {
    uint32_t start = pit_ticks;
    while ((pit_ticks - start) < ms)
        __asm__ volatile ("hlt");
}

static void pit_irq_handler(registers_t *regs) {
    (void)regs;
    pit_ticks++;
}

void pitInit(uint32_t freq) {
    uint32_t div = 1193180 / freq;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(div & 0xFF));
    outb(0x40, (uint8_t)((div >> 8) & 0xFF));

    irqRegisterHandler(0, pit_irq_handler);

    printf("PIT: %COK%C  (%d Hz)\n", GREEN, WHITE, freq);
}