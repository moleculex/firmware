#include "platform_config.h"
#include "display.h"
#include "output.h"

void display_show(char id, char state)
{
	output_digitalWrite(id, state);
}
