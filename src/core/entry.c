#include "./inc/stdio.h"
#include "./inc/gdt.h"
#include "./inc/isr.h"
#include "./inc/pit.h"

void kentry(unsigned int mag, unsigned int *inf) {
    tInit();
    gdtInit();
    isrInit();
    pitInit(100);
    __asm__ volatile ("sti");

    printf("Welcome to 24Os!\n");

    uchar code[] = {0xB8, 0x64, 0x00, 0x00, 0x00,
                    0x31, 0xD2,
                    0xB9, 0x00, 0x00, 0x00, 0x00,
                    0xF7, 0xF1,
                    0xC3};

    void (*main)() = (void(*)())code;

    uint last = 0;
    while (1) {
        main(); // will drop DE
        __asm__ volatile ("hlt");
    }
}