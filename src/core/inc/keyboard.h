#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

#define KEYBOARD_BUFFER_SIZE 256

void keyboardInit(void);
char keyboard_extra(void);
void keyboardReadLine(char *b, uint max);

#endif