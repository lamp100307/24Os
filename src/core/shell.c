#include "../inc/stdio.h"
#include "../inc/string.h"
#include "../inc/keyboard.h"
#include "../inc/hist.h"

static void sh_exe(char *c) {
    if (!strcmp(c, "clear") || !strcmp(c, "clr")) clear();
    else if (!strncmp(c, "echo ", 5)) printf("%s\n", c + 5);
    else if (!strcmp(c, "echo")) putc('\n');
    else if (*c) { printf("Unknown command: %s\n", c); }
}

void sh_loop(void) {
    char b[128];
    int l = 0;
    printf("%C24os%C/%Croot%C> ", RED, WHITE, BLUE, WHITE);
    h_rst();
    while (1) {
        char c = keyboard_extra();
        if (c == '\n') {
            b[l] = 0; putc('\n');
            h_add(b);
            sh_exe(b);
            l = 0; h_rst();
            printf("%C24os%C/%Croot%C> ", RED, WHITE, BLUE, WHITE);
        } else if (c == 11) {
            clear();
            b[l] = 0; 
            printf("%C24os%C/%Croot%C> %s", RED, WHITE, BLUE, WHITE, b);
        } else if (c == 17 || c == 18) {
            const char *h = (c == 17) ? h_up() : h_dn();
            if (h) {
                while (l > 0) { l--; putc('\b'); putc(' '); putc('\b'); }
                strcpy(b, h); l = strlen(b);
                printf("%s", b);
            }
        } else if (c == '\b') {
            if (l > 0) { l--; putc('\b'); putc(' '); putc('\b'); }
        } else if (l < 127) {
            b[l++] = c; putc(c);
        }
    }
}