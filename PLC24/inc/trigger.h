#ifndef __TRIGGER_H
#define __TRIGGER_H

#include "stm32f30x.h"

#define PB 0
#define IR 1

typedef struct{
	char a;
	char a_cnt;
	char a_cnt_en;
	char b;
	char b_cnt;
	char b_cnt_en;
}t_trigger;

t_trigger _trigger;

int16_t  trigger_read(char id);

#endif
