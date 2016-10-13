#include "led.h"
#include "_74HC595.h"

void led_input(int8_t line, int8_t state)
{
	switch(line)
	{
		case 0:
			if(state == 1)
				_led.buffer[5] |= 0x01;
			else
				_led.buffer[5] &= 0xFE;

			break;

		case 1:
			if(state == 1)
				_led.buffer[5] |= 0x02;
			else
				_led.buffer[5] &= 0xFD;

			break;

		case 2:
			if(state == 1)
				_led.buffer[5] |= 0x04;
			else
				_led.buffer[5] &= 0xFB;

			break;

		case 3:
			if(state == 1)
				_led.buffer[5] |= 0x08;
			else
				_led.buffer[5] &= 0xF7;

			break;

		case 4:
			if(state == 1)
				_led.buffer[5] |= 0x10;
			else
				_led.buffer[5] &= 0xEF;

			break;

		case 5:
			if(state == 1)
				_led.buffer[5] |= 0x20;
			else
				_led.buffer[5] &= 0xDF;

			break;

		case 6:
			if(state == 1)
				_led.buffer[5] |= 0x40;
			else
				_led.buffer[5] &= 0xBF;

			break;

		case 7:
			if(state == 1)
				_led.buffer[5] |= 0x80;
			else
				_led.buffer[5] &= 0x7F;

			break;

		case 8:
			if(state == 1)
				_led.buffer[4] |= 0x01;
			else
				_led.buffer[4] &= 0xFE;

			break;

		case 9:
			if(state == 1)
				_led.buffer[4] |= 0x02;
			else
				_led.buffer[4] &= 0xFD;

			break;

		case 10:
			if(state == 1)
				_led.buffer[4] |= 0x04;
			else
				_led.buffer[4] &= 0xFB;

			break;

		case 11:
			if(state == 1)
				_led.buffer[4] |= 0x08;
			else
				_led.buffer[4] &= 0xF7;

			break;

		case 12:
			if(state == 1)
				_led.buffer[4] |= 0x10;
			else
				_led.buffer[4] &= 0xEF;

			break;

		case 13:
			if(state == 1)
				_led.buffer[4] |= 0x20;
			else
				_led.buffer[4] &= 0xDF;

			break;

		case 14:
			if(state == 1)
				_led.buffer[4] |= 0x40;
			else
				_led.buffer[4] &= 0xBF;

			break;

		case 15:
			if(state == 1)
				_led.buffer[4] |= 0x80;
			else
				_led.buffer[4] &= 0x7F;

			break;

		case 20:
			if(state == 1)
				_led.buffer[3] |= 0x01;
			else
				_led.buffer[3] &= 0xFE;

			break;

		case 21:
			if(state == 1)
				_led.buffer[3] |= 0x02;
			else
				_led.buffer[3] &= 0xFD;

			break;

		case 22:
			if(state == 1)
				_led.buffer[3] |= 0x04;
			else
				_led.buffer[3] &= 0xFB;

			break;

		case 23:
			if(state == 1)
				_led.buffer[3] |= 0x08;
			else
				_led.buffer[3] &= 0xF7;

			break;

		case 16:
			if(state == 1)
				_led.buffer[3] |= 0x10;
			else
				_led.buffer[3] &= 0xEF;

			break;

		case 17:
			if(state == 1)
				_led.buffer[3] |= 0x20;
			else
				_led.buffer[3] &= 0xDF;

			break;

		case 18:
			if(state == 1)
				_led.buffer[3] |= 0x40;
			else
				_led.buffer[3] &= 0xBF;

			break;

		case 19:
			if(state == 1)
				_led.buffer[3] |= 0x80;
			else
				_led.buffer[3] &= 0x7F;

			break;

	}

	_74HC595_cs(0);
	_74HC595_write(_led.buffer, 6);
	_74HC595_cs(1);
}

void led_output(int8_t line, int8_t state)
{
	switch(line)
	{
		case 0:
			if(state == 1)
				_led.buffer[2] |= 0x80;
			else
				_led.buffer[2] &= 0x7F;

			break;

		case 1:
			if(state == 1)
				_led.buffer[2] |= 0x40;
			else
				_led.buffer[2] &= 0xBF;

			break;

		case 2:
			if(state == 1)
				_led.buffer[2] |= 0x20;
			else
				_led.buffer[2] &= 0xDF;

			break;

		case 3:
			if(state == 1)
				_led.buffer[2] |= 0x10;
			else
				_led.buffer[2] &= 0xEF;

			break;

		case 4:
			if(state == 1)
				_led.buffer[2] |= 0x08;
			else
				_led.buffer[2] &= 0xF7;

			break;

		case 5:
			if(state == 1)
				_led.buffer[2] |= 0x04;
			else
				_led.buffer[2] &= 0xFB;

			break;

		case 6:
			if(state == 1)
				_led.buffer[2] |= 0x02;
			else
				_led.buffer[2] &= 0xFD;

			break;

		case 7:
			if(state == 1)
				_led.buffer[2] |= 0x01;
			else
				_led.buffer[2] &= 0xFE;

			break;

		case 8:
			if(state == 1)
				_led.buffer[1] |= 0x80;
			else
				_led.buffer[1] &= 0x7F;

			break;

		case 9:
			if(state == 1)
				_led.buffer[1] |= 0x40;
			else
				_led.buffer[1] &= 0xBF;

			break;

		case 10:
			if(state == 1)
				_led.buffer[1] |= 0x20;
			else
				_led.buffer[1] &= 0xDF;

			break;

		case 11:
			if(state == 1)
				_led.buffer[1] |= 0x10;
			else
				_led.buffer[1] &= 0xEF;

			break;

		case 12:
			if(state == 1)
				_led.buffer[1] |= 0x08;
			else
				_led.buffer[1] &= 0xF7;

			break;

		case 13:
			if(state == 1)
				_led.buffer[1] |= 0x04;
			else
				_led.buffer[1] &= 0xFB;

			break;

		case 14:
			if(state == 1)
				_led.buffer[1] |= 0x02;
			else
				_led.buffer[1] &= 0xFD;

			break;

		case 15:
			if(state == 1)
				_led.buffer[1] |= 0x01;
			else
				_led.buffer[1] &= 0xFE;

			break;

		case 16:
			if(state == 1)
				_led.buffer[0] |= 0x80;
			else
				_led.buffer[0] &= 0x7F;

			break;

		case 17:
			if(state == 1)
				_led.buffer[0] |= 0x40;
			else
				_led.buffer[0] &= 0xBF;

			break;

		case 18:
			if(state == 1)
				_led.buffer[0] |= 0x20;
			else
				_led.buffer[0] &= 0xDF;

			break;

		case 19:
			if(state == 1)
				_led.buffer[0] |= 0x10;
			else
				_led.buffer[0] &= 0xEF;

			break;

		case 20:
			if(state == 1)
				_led.buffer[0] |= 0x08;
			else
				_led.buffer[0] &= 0xF7;

			break;

		case 21:
			if(state == 1)
				_led.buffer[0] |= 0x04;
			else
				_led.buffer[0] &= 0xFB;

			break;

		case 22:
			if(state == 1)
				_led.buffer[0] |= 0x02;
			else
				_led.buffer[0] &= 0xFD;

			break;

		case 23:
			if(state == 1)
				_led.buffer[0] |= 0x01;
			else
				_led.buffer[0] &= 0xFE;

			break;
	}

	_74HC595_cs(0);
	_74HC595_write(_led.buffer, 6);
	_74HC595_cs(1);
}
