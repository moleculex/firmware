#ifndef __74HC595_H
#define __74HC595_H

void _74HC595_init(void);
void _74HC595_write(char *buffer, int length);
void _74HC595_cs(char state);

#endif
