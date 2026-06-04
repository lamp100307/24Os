#include "../inc/string.h"

#define MAX 16
#define LEN 128

static char h[MAX][LEN];
static int c = 0;
static int i = -1;

void h_add(const char *s) {
    if (!s || !*s) return;
    if (c > 0 && !strcmp(h[(c - 1) % MAX], s)) { i = c; return; }
    strcpy(h[c % MAX], s);
    i = ++c;
}

const char *h_up() {
    return (c == 0 || i <= 0) ? NULL : h[--i % MAX];
}

const char *h_dn() {
    return (i >= c) ? NULL : (++i == c ? "" : h[i % MAX]);
}

void h_rst() {
    i = c;
}