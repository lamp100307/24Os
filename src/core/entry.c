#include "./inc/stdio.h"
#include "./inc/gdt.h"
#include "./inc/isr.h"
#include "./inc/pit.h"
#include "./inc/keyboard.h"
#include "./inc/pmm.h"
#include "./inc/vmm.h"
#include "./inc/shell.h"

extern uint end;
void kentry(unsigned int mag, unsigned int *inf) {
    tInit();
    gdtInit();
    isrInit();
    pitInit(100);
    keyboardInit();

    size_t ram = (mag == 0x2BADB002 && inf) ? (inf[2] * 1024) + (1024 * 1024) : (32 * 1024 * 1024); // TODO: надо чета делать (32 * 1024 * 1024) а то это фигня какая-то если не нашло просто писать 32 мб

    pmminit(ram, (uintptr_t)&end);
    vmminit();

    __asm__ volatile ("sti");

    printf("Welcome to 24Os!\n");
    printf("RAM: %d MB.\n", ram / (1024 * 1024));

    sh_loop();
}