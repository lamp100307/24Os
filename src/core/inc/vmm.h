#ifndef VMM_H
#define VMM_H

#include "types.h"

void vmminit(void);
void vmmmap(uintptr_t v, uintptr_t f, int usr);
void vmmswitch(uintptr_t dir);

#endif