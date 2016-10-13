#include "platform_config.h"
#include "input.h"
#include "trigger.h"

int16_t trigger_read(char id)
{
	return input_digitalRead(id);
}

