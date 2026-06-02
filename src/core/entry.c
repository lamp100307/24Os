void kentry(unsigned int mag, unsigned int *inf) {
        (void)mag;
        (void)inf;
        while (1) {
            __asm__ volatile("hlt");
        }
}