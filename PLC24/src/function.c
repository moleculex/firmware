#ifdef USE_PLCLIB
#include <plcLib.h>
#include "function.h"

void function_init()
{
	_function.buffer_ptr = &_function.buffer[0];
}

/*
 * STEP 1 AND
 * STEP 2 AND
 * STEP 3
 */
//01302
void function_interpreter(void)
{
	for(int16_t i = 0; i < 128; i+2)
	{
		switch(_function.buffer[i])
		{
		case FR_IN:
			in(_function.buffer[i+1]);
			break;

		case FR_AND:
			andBit(_function.buffer[i+1]);
			break;

		case FR_OR:
			orBit(_function.buffer[i+1]);
			break;

		case FR_SET:
			set(_function.buffer[i+1]);
			break;

		case FR_RESET:
			reset(_function.buffer[i+1]);
			break;

		case FR_OUT:
			out(_function.buffer[i+1]);
			break;
		}
}
#endif

