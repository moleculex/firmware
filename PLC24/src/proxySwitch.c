#include "input.h"
#include "proxySwitch.h"

int16_t proxySwitch_read(char id)
{
	return input_digitalRead(id);
}
