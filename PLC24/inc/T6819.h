#ifndef __T6819_H
#define __T6819_H

void T6819_init(void);
void T6819_write(char *buffer, int length);
void T6819_cs(char state);

#endif
