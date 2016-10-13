#ifndef __FUNCTION_H
#define __FUNCTION_H
#ifdef USE_PLCLIB
#include "stm32f30x.h"

typedef enum
{
	FR_IN = 0,
	FR_AND,
	FR_OR,
	FR_SET,
	FR_RESET,
	FR_OUT
}t_framework;


typedef struct
{
	int8_t buffer[128];
	int8_t *buffer_ptr;
}t_function;

t_function _function;

void function_init(void);
void function_interpreter(void);
#endif

#endif
