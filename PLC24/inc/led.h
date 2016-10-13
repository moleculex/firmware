#ifndef __LED_H
#define __LED_H

#include "stm32f30x.h"

typedef struct{
	char buffer[6];
}t_led;

t_led _led;

void led_output(int8_t line, int8_t state);
void led_input(int8_t line, int8_t state);

#endif
