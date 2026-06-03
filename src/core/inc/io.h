#ifndef IO_H
#define IO_H
#include "types.h"
static inline void outb(ushort port, uchar val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline uchar inb(ushort port) {
    uchar val;
    __asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}
static inline void outw(ushort port, ushort val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}
static inline ushort inw(ushort port) {
    ushort val;
    __asm__ volatile ("inw %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}
static inline void outl(ushort port, uint val) {
    __asm__ volatile ("outl %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint inl(ushort port) {
    uint val;
    __asm__ volatile ("inl %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}
static inline void io_wait(void) {
    outb(0x80, 0);
}
#endif