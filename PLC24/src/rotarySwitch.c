#include "platform_config.h"
#include "input.h"
#include "rotarySwitch.h"

char rotarySwitch_read(char pos)
{
	return  input_digitalRead(pos);
}
