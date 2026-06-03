#include "../inc/stdio.h"

void putn(unsigned int n, int base) {
    if (n >= (unsigned int)base) putn(n / base, base);
    putc("0123456789ABCDEF"[n % base]);
}

void printf(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    for (const char *p = fmt; *p; p++) {
        if (*p != '%') { putc(*p); continue; }
        switch (*++p) {
            case 'c': putc((char)va_arg(arg, int)); break;
            case 's': puts(va_arg(arg, char*)); break;
            case 'd': putd(va_arg(arg, int)); break;
            case 'x': putn(va_arg(arg, unsigned int), 16); break;
            case 'b': putn(va_arg(arg, unsigned int), 2); break;
            case 'C': setcolor(BLACK, va_arg(arg, enum vgaColor)); break;
            case '%': putc('%'); break;
        }
    }
    va_end(arg);
}

void tInit() {
    currentColor = GET_COLOR(BLACK, WHITE);
    cursorX = 0; cursorY = 0;
    clear();
}

void putc(char c) {
    if (c == '\n') { cursorX = 0; cursorY++; }
    else if (c == '\r') { cursorX = 0; }
    else {
        VGA_MEM[cursorY * VGA_WIDTH + cursorX] = GET_CHAR(c, currentColor);
        cursorX++;
    }
    if (cursorX >= VGA_WIDTH) { cursorX = 0; cursorY++; }
    if (cursorY >= VGA_HEIGHT) { scroll(); cursorY = VGA_HEIGHT - 1; }
}

void puts(const char *s) { while (*s) putc(*s++); }

void putd(int n) {
    if (n < 0) { putc('-'); if (n == -2147483648) { puts("2147483648"); return; } n = -n; }
    if (n / 10) putd(n / 10);
    putc('0' + (n % 10));
}

void setcolor(enum vgaColor bg, enum vgaColor fg) { currentColor = GET_COLOR(bg, fg); }

void clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) VGA_MEM[i] = GET_CHAR(' ', currentColor);
    cursorX = cursorY = 0;
}

void setcursor(int x, int y) { cursorX = x; cursorY = y; }

void scroll() {
    for (int i = VGA_WIDTH; i < VGA_WIDTH * VGA_HEIGHT; i++) VGA_MEM[i - VGA_WIDTH] = VGA_MEM[i];
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_WIDTH * VGA_HEIGHT; i++) VGA_MEM[i] = GET_CHAR(' ', currentColor);
}