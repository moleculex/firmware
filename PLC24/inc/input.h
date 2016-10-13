#ifndef __INPUT_H
#define __INPUT_H

#include "stm32f30x.h"

void input_digitalInit(void);

int16_t input_digitalRead(int8_t line);

#endif
