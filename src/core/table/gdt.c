#include "gdt.h"
#include "../inc/stdio.h"

static struct GDTE gdt[3];
static struct GDTD gdt_desc;

extern void gdtflush(uint);

static void setGdtGate(int n, uint b, uint l, uchar a, uchar g) {
    gdt[n].base_low = (b & 0xFFFF);
    gdt[n].base_middle = (b >> 16) & 0xFF;
    gdt[n].base_high = (b >> 24) & 0xFF;
    gdt[n].limit_low = (l & 0xFFFF);
    gdt[n].granularity = ((l >> 16) & 0x0F) | (g & 0xF0);
    gdt[n].access = a;
}

void gdtInit() {
    gdt_desc.size = (sizeof(struct GDTE) * 3) - 1;
    gdt_desc.offset = (uint)&gdt;

    setGdtGate(0, 0, 0, 0, 0);
    setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdtflush((uint)&gdt_desc);

    if (gdt_desc.offset != 0) {
        printf("GDT: %COK %C\n", GREEN, WHITE);
    } else {
        printf("GDT: %CBAD %C\n", RED, WHITE);
    }
}