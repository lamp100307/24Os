#ifndef ISR_H
#define ISR_H

#include "types.h"

typedef struct {
    uint ds;
    uint edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint int_no, err_code;
    uint eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);
void isrRegisterHandler(uchar n, isr_t handler);
typedef void (*irq_t)(registers_t *);

void irqRegisterHandler(uchar irq, irq_t handler);
void isr_handler(registers_t *regs);
void irq_handler(registers_t *regs);
void isrInit(void);

extern const char *exception_messages[32];

#endif