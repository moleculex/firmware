#ifndef __ROTARYSWITCH_H
#define __ROTARYSWITCH_H

typedef struct{
	char sw1;
	char sw2;
	char sw3;
}t_rotarySwitch;
t_rotarySwitch _rotarySwitch;

char rotarySwitch_read(char pos);

#endif
