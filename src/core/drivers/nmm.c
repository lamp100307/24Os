#include "nmm.h"
typedef struct header {
    struct header *next;
    size_t size;
    char free;
} header_t;
static header_t *root = NULL;
static uintptr_t top = HEAPSTART;
static void memgrow(size_t sz) {
    size_t req = sz + sizeof(header_t);
    size_t blks = req / PMM_BLOCK_SIZE;
    if (req % PMM_BLOCK_SIZE) blks++;
    header_t *last = root;
    if (last) {while (last->next) last = last->next;}
    for (size_t i=0; i <blks; i++) {
        void *p = pmmalloc();
        if (!p) return;
        vmmmap(top, (uintptr_t)p,0);
        header_t *h = (header_t *)top;
        h->size=PMM_BLOCK_SIZE-sizeof(header_t);
        h->free=1;
        h->next=NULL;
        if (!root) root=h;
        else last->next=h;
        last=h;
        top+=PMM_BLOCK_SIZE;
    }
}
void nmminit(void) {
    memgrow(4096);
    printf("%CNMM:%COK%C\n", WHITE, GREEN, WHITE);
}
void *kmalloc(size_t sz) {
    if (!sz) return NULL;
    header_t *curr = root;
    while (curr) {
        if(curr->free && curr->size >= sz) {
            if (curr->size >= sz + sizeof(header_t) + 4) {
                header_t *new = (header_t *)((uintptr_t)curr + sizeof(header_t) + sz);
                new->next = curr->next;
                new->size = curr->size - sz - sizeof(header_t);
                new->free = 1;
                curr->next = new;
                curr->size = sz;
            }
            curr->free = 0;
            return (void *)((uintptr_t)curr + sizeof(header_t));
        }
        curr = curr->next;
    }
    memgrow(sz);
    return kmalloc(sz);
}

void kfree(void *p) {
    if (!p) return;
    header_t *hdr = (header_t *)((uintptr_t)p - sizeof(header_t));
    hdr->free = 1;
    header_t *curr = root;
    while (curr) {
        if (curr->free && curr->next && curr->next->free) {
            curr->size += sizeof(header_t) + curr->next->size;
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }   
}
// TODO: сделать buddy allocator, а не просто linked list, а то это фигня какая-то будет, и так же сделать memgrow через pmm, а не просто двигать top