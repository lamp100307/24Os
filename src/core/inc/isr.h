#ifndef ISR_H
#define ISR_H

#include <types.h>

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);
void isrRegisterHandler(uint8_t n, isr_t handler);
typedef void (*irq_t)(registers_t *);

void irqRegisterHandler(uint8_t irq, irq_t handler);
void isr_handler(registers_t *regs);
void irq_handler(registers_t *regs);
void isrInit(void);

extern const char *exception_messages[32];

#endif