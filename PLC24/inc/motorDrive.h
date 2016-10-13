#ifndef __MOTORDRIVE_H
#define __MOTORDRIVE_H

#include "stm32f30x.h"

typedef enum{
	STOP = 0,
	OPEN,
	CLOSE
}MOTOR_DRIVE;

void motorDrive_control(char mode, int8_t rfr, int8_t di1, int8_t di2);

#endif
