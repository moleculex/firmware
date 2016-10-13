#ifndef __IR_H
#define __IR_H

#include "stm32f30x.h"

typedef struct{
	char a_ext;
	char a_int;
	char b_int;
	char b_ext;
	char crawl;
}t_ir;
t_ir _ir;

int16_t ir_rx(char id);

#endif
