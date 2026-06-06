#include "../inc/pmm.h"
#include "../inc/string.h"
#include "../inc/stdio.h"

static uint32_t *map;
static size_t blks = 0;
static size_t usd = 0;

void pmminit(size_t sz, uintptr_t ram) {
    blks = sz / PMM_BLOCK_SIZE;
    map = (uint32_t*)ram;
    size_t msz = blks / 32;
    if (blks % 32) msz++;
    memset(map, 0xFF, msz * 4);
    usd = blks;
    uintptr_t fst = ram + (msz * 4);
    fst = (fst + PMM_BLOCK_SIZE - 1) & ~(PMM_BLOCK_SIZE - 1);
    size_t sblk = fst / PMM_BLOCK_SIZE;
    for (size_t i = sblk; i < blks; i++) {
        map[i / 32] &= ~(1 << (i % 32));
        usd--;
    }
    size_t free = blks - usd;
    printf("%CPMM %COK%C\n", WHITE, GREEN, WHITE);
    printf("  RAM Size     : %x bytes\n", sz);
    printf("  Bitmap Addr  : %x\n", ram);
    printf("  Total Blocks : %x\n", blks);
    printf("  Used Blocks  : %x\n", usd);
    printf("  Free Blocks  : %x\n", free);
    printf("  Block Size   : %x bytes\n", PMM_BLOCK_SIZE);
}

void *pmmalloc(void) {
    for (size_t i = 0; i < blks / 32; i++) {
        if (map[i] != 0xFFFFFFFF) {
            for (int b = 0; b < 32; b++) {
                if (!(map[i] & (1 << b))) { 
                    size_t blk = i * 32 + b;
                    map[i] |= (1 << b);
                    usd++;
                    return (void*)(blk * PMM_BLOCK_SIZE);
                }
            }
        }
    }
    return NULL;
}

void pmmfree(void *p) {
    uintptr_t adr = (uintptr_t)p;
    size_t blk = adr / PMM_BLOCK_SIZE;
    if (blk < blks && (map[blk / 32] & (1 << (blk % 32)))) {
        map[blk / 32] &= ~(1 << (blk % 32));
        usd--;
    }
}