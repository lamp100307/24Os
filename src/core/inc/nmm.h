#ifndef NMM_H
#define NMM_H

#include "types.h"
#include "pmm.h"
#include "vmm.h"
#include "stdio.h"

#define HEAPSTART 0xC0000000
#define CHUNKSZ 512

void nmminit(void);
void *kmalloc(size_t sz);
void kfree(void *p);

#endif // NMM_H