#include "platform_config.h"
#include "input.h"
#include "ir.h"

int16_t ir_rx(char id)
{
	return input_digitalRead(id);
}

