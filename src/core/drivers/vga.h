#ifndef VGA_H
#define VGA_H

#include "types.h"

enum vgaColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
};

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDR 0xB8000
#define VGA_MEM ((volatile ushort*)VGA_ADDR)
#define GET_COLOR(bg, fg) (fg | bg << 4)
#define GET_CHAR(c, color) ((ushort)c | ((ushort)color << 8))

static ushort currentColor = GET_COLOR(BLACK, WHITE);
static int cursorX = 0, cursorY = 0;

void vgaPutc(char c);
void setColor(enum vgaColor bg, enum vgaColor fg);
void vgaClear();
void vgaInit();
void vgaPuts(char* str);
void vgaPutd(int d);
void vgaScroll();
void vgaSetCursor(int x, int y);

#endif