#ifndef PIT_H
#define PIT_H

#include <types.h>

void pitInit(uint32_t freq);
uint32_t pitGetTicks(void);
void pitSleep(uint32_t ms);

#endif