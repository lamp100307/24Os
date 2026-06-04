#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

#define KEYBOARD_BUFFER_SIZE 256

void keyboardInit(void);
void keyboardReadLine(char *buf, uint max);

#endif