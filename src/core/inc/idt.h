#ifndef IDT_H
#define IDT_H

#include "types.h"

struct IDTE {
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct IDTP {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idtInit();
void setIdtGate(int n, uint32_t base, uint16_t sel, uint8_t flags);

#endif