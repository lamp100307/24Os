#ifndef PMM_H
#define PMM_H

#include "types.h"

#define PMM_BLOCK_SIZE 4096

void pmminit(size_t sz, uintptr_t ram);
void *pmmalloc(void);
void pmmfree(void *p);

#endif