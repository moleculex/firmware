#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "stm32f30x.h"
#define HIGH 1
#define LOW 0
typedef struct{
	char buffer[16];
}t_output;

t_output _output;

void output_digitalWrite(int8_t line, int8_t state);

#endif
