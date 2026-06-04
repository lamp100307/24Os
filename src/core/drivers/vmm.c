#include "../inc/vmm.h"
#include "../inc/pmm.h"
#include "../inc/string.h"

static uint32_t *pdr = NULL;

void vmmswitch(uintptr_t dir) {
    __asm__ volatile("mov %0, %%cr3" :: "r"(dir));
    uint32_t c0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(c0));
    c0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" :: "r"(c0));
}

void vmmmap(uintptr_t v, uintptr_t f, int usr) {
    uint32_t pdi = v >> 22;
    uint32_t pti = (v >> 12) & 0x3FF;
    uint32_t flg = 3 | (usr ? 4 : 0);
    if (!(pdr[pdi] & 1)) {
        void *pt = pmmalloc();
        memset(pt, 0, PMM_BLOCK_SIZE);
        pdr[pdi] = (uintptr_t)pt | flg;
    }
    uint32_t *pt = (uint32_t *)(pdr[pdi] & ~0xFFF);
    pt[pti] = (f & ~0xFFF) | flg;
}

void vmminit(void) {
    pdr = (uint32_t *)pmmalloc();
    memset(pdr, 0, PMM_BLOCK_SIZE);
    for (uintptr_t i = 0; i < 0x40000000; i += PMM_BLOCK_SIZE) {
        vmmmap(i, i, 0);
    }
    vmmswitch((uintptr_t)pdr);
}