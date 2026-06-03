#ifndef IDT_H
#define IDT_H

#include "types.h"

struct IDTE {
    ushort base_low;
    ushort sel;
    uchar zero;
    uchar flags;
    ushort base_high;
} __attribute__((packed));

struct IDTP {
    ushort limit;
    uint base;
} __attribute__((packed));

void idtInit();
void setIdtGate(int n, uint base, ushort sel, uchar flags);

#endif