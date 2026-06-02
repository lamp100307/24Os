#include "stdio.h"
#include "gdt.h"
#include "isr.h"
#include "pit.h"

void kentry(unsigned int mag, unsigned int *inf) {
    tInit();
    gdtInit();
    isrInit();
    pitInit(100);
    __asm__ volatile ("sti");

    printf("Welcome to 24Os %d!\n", 10);

    uint32_t last = 0;
    while (1) {
        __asm__ volatile ("hlt");

        uint32_t ticks = pitGetTicks();
        if (ticks - last >= 10) {
            printf("Ticks: %d\n", ticks);
        }
    }
}