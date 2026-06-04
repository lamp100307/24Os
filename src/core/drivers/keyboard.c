#include "../inc/keyboard.h"
#include "../inc/isr.h"
#include "../inc/io.h"
#include "../inc/stdio.h"

static volatile char caps = 0;
static volatile char ctrl = 0;
static volatile char e0 = 0;
static volatile char buf[KEYBOARD_BUFFER_SIZE];
static volatile uint wr = 0;   
static volatile uint rd = 0;   

static const uchar scl[128] = {
    0,    0x1B, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t', 'q','w','e','r','t','y','u','i','o','p','[',']', '\n',
    0,    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,   '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0,   ' '
};

static const uchar scu[128] = {
    0,    0x1B, '!','@','#','$','%','^','&','*','(',')','_','+', '\b',
    '\t', 'Q','W','E','R','T','Y','U','I','O','P','{','}', '\n',
    0,    'A','S','D','F','G','H','J','K','L',':','"','~',
    0,   '|','Z','X','C','V','B','N','M','<','>','?', 0,
    '*', 0,   ' '
};

static void kbd_enqueue(char c) {
    uint nxt = (wr + 1) % KEYBOARD_BUFFER_SIZE;
    if (nxt != rd) {            
        buf[wr] = c;
        wr = nxt;
    }
}

static char kbd_dequeue(void) {
    while (rd == wr) __asm__ volatile ("hlt");
    char c = buf[rd];
    rd = (rd + 1) % KEYBOARD_BUFFER_SIZE;
    return c;
}

static void keyboardCallback(registers_t *r) {
    (void)r;
    uchar sc = inb(0x60);
    if (sc == 0xE0) { e0 = 1; return; }
    if (sc & 0x80) {
        if ((sc & 0x7F) == 0x1D) ctrl = 0;
        e0 = 0; return;
    }
    if (sc == 0x1D) { ctrl = 1; e0 = 0; return; }
    if (sc == 0x3A) { caps = !caps; e0 = 0; return; }
    if (e0) {
        e0 = 0;
        if (sc == 0x48) kbd_enqueue(17);
        if (sc == 0x50) kbd_enqueue(18);
        return;
    }
    if (ctrl && sc == 0x26) { kbd_enqueue(11); return; }
    uchar c = caps ? scu[sc] : scl[sc];
    if (c) kbd_enqueue(c);
}

void keyboardInit(void) {
    irqRegisterHandler(1, keyboardCallback);
    printf("Keyboard: %COK%C\n", GREEN, WHITE);
}

char keyboard_extra(void) {
    return kbd_dequeue();
}

void keyboardReadLine(char *b, uint max) {
    if (!max) return;
    uint i = 0;
    while (1) {
        char c = kbd_dequeue();
        if (c == '\n') {
            if (i < max) b[i] = 0;
            putc('\n');
            return;
        }
        if (c == '\b' || c == 0x7F) {   
            if (i > 0) { i--; putc('\b'); putc(' '); putc('\b'); }
            continue;
        }
        if (i < max - 1) { b[i++] = c; putc(c); }
    }
}