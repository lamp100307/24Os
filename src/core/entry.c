#include "./inc/stdio.h"
#include "./inc/gdt.h"
#include "./inc/isr.h"
#include "./inc/pit.h"
#include "./inc/keyboard.h"

void kentry(unsigned int mag, unsigned int *inf) {
    tInit();
    gdtInit();
    isrInit();
    pitInit(100);
    keyboardInit();
    __asm__ volatile ("sti");

    printf("Welcome to 24Os!\n");

    uint last = 0;
    while (1) {
        printf("> ");
        char command [128];
        keyboardReadLine(command, 128);
        if (command[0] == 'e' && command[1] == 'c' && command[2] == 'h' && command[3] == 'o') {
            char* start = &command[4];
            while (*start != '\0') {
                printf("%c\n", *start);
                start++;
            }
        }
        __asm__ volatile ("hlt");
    }
}