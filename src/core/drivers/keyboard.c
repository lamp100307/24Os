#include "../inc/keyboard.h"
#include "../inc/isr.h"
#include "../inc/io.h"
#include "../inc/stdio.h"

static volatile char  isCaps = 0;
static volatile char  kbd_buf[KEYBOARD_BUFFER_SIZE];
static volatile uint  kbd_wr = 0;   
static volatile uint  kbd_rd = 0;   


static const uchar sc_lower[128] = {
    0,    0x1B, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t', 'q','w','e','r','t','y','u','i','o','p','[',']', '\n',
    0,    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,   '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0,   ' ', 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static const uchar sc_upper[128] = {
    0,    0x1B, '!','@','#','$','%','^','&','*','(',')','_','+', '\b',
    '\t', 'Q','W','E','R','T','Y','U','I','O','P','{','}', '\n',
    0,    'A','S','D','F','G','H','J','K','L',':','"','~',
    0,   '|','Z','X','C','V','B','N','M','<','>','?', 0,
    '*', 0,   ' ', 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static void kbd_enqueue(char c) {
    uint next = (kbd_wr + 1) % KEYBOARD_BUFFER_SIZE;
    if (next != kbd_rd) {            
        kbd_buf[kbd_wr] = c;
        kbd_wr = next;
    }
}

static char kbd_dequeue(void) {
    while (kbd_rd == kbd_wr) {
        
        __asm__ volatile ("hlt");
    }
    char c = kbd_buf[kbd_rd];
    kbd_rd = (kbd_rd + 1) % KEYBOARD_BUFFER_SIZE;
    return c;
}

/* --- Обработчик прерывания от клавиатуры (только трансляция) --- */
static void keyboardCallback(registers_t *regs) {
    (void)regs;
    uchar sc = inb(0x60);
    if (sc & 0x80) return;           

    
    if (sc == 0x3A) {
        isCaps = !isCaps;
        return;
    }

    
    const uchar *table = isCaps ? sc_upper : sc_lower;
    uchar c = table[sc];

    if (c) {
        kbd_enqueue(c);
    }
}

/* --- Публичные функции --- */
void keyboardInit(void) {
    irqRegisterHandler(1, keyboardCallback);
    printf("Keyboard: %COK%C\n", GREEN, WHITE);
}

void keyboardReadLine(char *buf, uint max) {
    if (max == 0) return;

    uint i = 0;
    while (1) {
        char c = kbd_dequeue();

        if (c == '\n') {
            
            if (i < max) buf[i] = '\0';
            putc('\n');
            return;
        }

        if (c == '\b' || c == 0x7F) {   
            if (i > 0) {
                i--;
                
                putc('\b');
                putc(' ');
                putc('\b');
            }
            continue;
        }

        
        if (i < max - 1) {
            buf[i++] = c;
            putc(c);
        }
    }
}