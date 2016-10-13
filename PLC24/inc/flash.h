#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f30x.h"

void flash_write(char *buffer, int16_t length);
void flash_read(char *buffer, int16_t length);

#endif
