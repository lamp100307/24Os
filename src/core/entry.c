#include "drivers/vga.h"

void kentry(unsigned int mag, unsigned int *inf) {
    (void)mag;
    (void)inf;
    vgaInit();
    vgaPuts("Welcome to 24Os!\n");
    while (1) {
        __asm__ volatile("hlt");
    }
}