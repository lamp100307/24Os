#include "vga.h"

void vgaInit() {
    currentColor = GET_COLOR(BLACK, WHITE);
    cursorX = 0;
    cursorY = 0;
    vgaClear();
}

void vgaPutc(char c) {
    switch (c) {
        case '\n':
            cursorX = 0;
            cursorY++;
            break;
        case '\r':
            cursorX = 0;
            return;
        default:
            // Нормальный символ
            VGA_MEM[cursorY * VGA_WIDTH + cursorX] = GET_CHAR(c, currentColor);
            cursorX++;
            break;
    }
    
    if (cursorX >= VGA_WIDTH) {
        cursorX = 0;
        cursorY++;
    }
    
    if (cursorY >= VGA_HEIGHT) {
        vgaScroll();
        cursorY = VGA_HEIGHT - 1;
    }
}

void setColor(enum vgaColor bg, enum vgaColor fg) {
    currentColor = GET_COLOR(bg, fg);
}

void vgaClear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_MEM[i] = GET_CHAR(' ', currentColor);
    }
    cursorX = 0;
    cursorY = 0;
}

void vgaPuts(char *str) {
    while (*str) vgaPutc(*str++);
}

void vgaPutd(int num) {
    if (num < 0) {
        vgaPutc('-');
        if (num == -2147483648) {  
            vgaPuts("2147483648");
            return;
        }
        num = -num;
    }
    
    if (num / 10 != 0) {
        vgaPutd(num / 10);
    }
    vgaPutc('0' + (num % 10));
}

void setCursor(int x, int y) {
    cursorX = x;
    cursorY = y;
}

void vgaScroll() {
    // Копируем строки, начиная СНИЗУ ВВЕРХ, чтобы избежать перезаписи
    for (int i = 1; i < VGA_HEIGHT; i++) {
        // Копируем строку i на позицию i-1
        for (int j = 0; j < VGA_WIDTH; j++) {
            int src_index = i * VGA_WIDTH + j;
            int dst_index = (i - 1) * VGA_WIDTH + j;
            VGA_MEM[dst_index] = VGA_MEM[src_index];
        }
    }
    
    // Очищаем последнюю строку
    int last_line = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (int j = 0; j < VGA_WIDTH; j++) {
        VGA_MEM[last_line + j] = GET_CHAR(' ', currentColor);
    }
}