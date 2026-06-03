// src/core/inc/gdt.h
#ifndef GDT_H
#define GDT_H

#include "types.h"

struct GDTE {
    ushort limit_low;
    ushort base_low;
    uchar base_middle;
    uchar access;
    uchar granularity;
    uchar base_high;
} __attribute__((packed));

struct GDTD {
    ushort size;
    uint offset;
} __attribute__((packed));

void gdtInit();

#endif