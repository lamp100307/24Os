// src/core/inc/gdt.h
#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct GDTE {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDTD {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

void gdtInit();

#endif