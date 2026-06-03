#ifndef PIT_H
#define PIT_H

#include "types.h"

void pitInit(uint freq);
uint pitGetTicks(void);
void pitSleep(uint ms);

#endif