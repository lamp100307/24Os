#include "./inc/stdio.h"
#include "./inc/gdt.h"
#include "./inc/isr.h"
#include "./inc/pit.h"
#include "./inc/keyboard.h"
#include "./inc/shell.h"
void kentry(unsigned int mag, unsigned int *inf) {
    (void)mag; (void)inf;
    tInit();
    gdtInit();
    isrInit();
    pitInit(100);
    keyboardInit();
    __asm__ volatile ("sti");

    printf("Welcome to 24Os!\n");

    sh_loop();
}