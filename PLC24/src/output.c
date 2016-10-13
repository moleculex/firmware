#include "platform_config.h"
#include "output.h"
#include "T6819.h"
#include "led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//t6839

void output_digitalWrite(int8_t line, int8_t state)
{
	/*int n = 1;
	while(n < 15)
	{
		_output.buffer[n] = 0x40;
		n += 2;
	}*/

	switch(line)
	{
		case 23:
			if(state == 1)
			{
				_output.buffer[14] |= 0x20;
				_output.buffer[15] |= 0x03;
				led_output(23, 1);
			}
			else
			{
				_output.buffer[14] &= 0xDF;
				_output.buffer[15] &= 0xFF;
				led_output(23, 0);
			}

			break;

		case 22:
			if(state == 1)
			{
				_output.buffer[14] |= 0x08;
				_output.buffer[15] |= 0x03;
				led_output(22, 1);
			}
			else
			{
				_output.buffer[14] &= 0xF7;
				_output.buffer[15] &= 0xFF;
				led_output(22, 0);
			}

			break;

		case 21:
			if(state == 1)
			{
				_output.buffer[14] |= 0x02;
				_output.buffer[15] |= 0x03;
				led_output(21, 1);
			}
			else
			{
				_output.buffer[14] &= 0xFD;
				_output.buffer[15] &= 0xFF;
				led_output(21, 0);
			}

			break;

		case 20:
			if(state == 1)
			{
				_output.buffer[14] |= 0x00;
				_output.buffer[15] |= 0x83;
				led_output(20, 1);
			}
			else
			{
				_output.buffer[14] &= 0xFF;
				_output.buffer[15] &= 0x7F;
				led_output(20, 0);
			}

			break;

		case 19:
			if(state == 1)
			{
				_output.buffer[14] |= 0x00;
				_output.buffer[15] |= 0x23;
				led_output(19, 1);
			}
			else
			{
				_output.buffer[14] &= 0xFF;
				_output.buffer[15] &= 0xDF;
				led_output(19, 0);
			}

			break;

		case 18:
			if(state == 1)
			{
				_output.buffer[14] |= 0x00;
				_output.buffer[15] |= 0x0B;
				led_output(18, 1);
			}
			else
			{
				_output.buffer[14] &= 0xFF;
				_output.buffer[15] &= 0xF7;
				led_output(18, 0);
			}

			break;

		case 17:
			if(state == 1)
			{
				_output.buffer[10] |= 0x20;
				_output.buffer[11] |= 0x03;
				led_output(17, 1);
			}
			else
			{
				_output.buffer[10] &= 0xDF;
				_output.buffer[11] &= 0xFF;
				led_output(17, 0);
			}

			break;

		case 16:
			if(state == 1)
			{
				_output.buffer[10] |= 0x08;
				_output.buffer[11] |= 0x03;
				led_output(16, 1);
			}
			else
			{
				_output.buffer[10] &= 0xF7;
				_output.buffer[11] &= 0xFF;
				led_output(16, 0);
			}

			break;

		case 15:
			if(state == 1)
			{
				_output.buffer[10] |= 0x02;
				_output.buffer[11] |= 0x03;
				led_output(15, 1);
			}
			else
			{
				_output.buffer[10] &= 0xFD;
				_output.buffer[11] &= 0xFF;
				led_output(15, 0);
			}

			break;

		case 14:
			if(state == 1)
			{
				_output.buffer[10] |= 0x00;
				_output.buffer[11] |= 0x83;
				led_output(14, 1);
			}
			else
			{
				_output.buffer[10] &= 0xFF;
				_output.buffer[11] &= 0x7F;
				led_output(14, 0);
			}

			break;

		case 13:
			if(state == 1)
			{
				_output.buffer[10] |= 0x00;
				_output.buffer[11] |= 0x23;
				led_output(13, 1);
			}
			else
			{
				_output.buffer[10] &= 0xFF;
				_output.buffer[11] &= 0xDF;
				led_output(13, 0);
			}

			break;

		case 12:
			if(state == 1)
			{
				_output.buffer[10] |= 0x00;
				_output.buffer[11] |= 0x0B;
				led_output(12, 1);
			}
			else
			{
				_output.buffer[10] &= 0xFF;
				_output.buffer[11] &= 0xF7;
				led_output(12, 0);
			}

			break;

		case 11:
			if(state == 1)
			{
				_output.buffer[6] |= 0x20;
				_output.buffer[7] |= 0x03;
				led_output(1, 1);
			}
			else
			{
				_output.buffer[6] &= 0xDF;
				_output.buffer[7] &= 0xFF;
				led_output(11, 0);
			}

			break;

		case 10:
			if(state == 1)
			{
				_output.buffer[6] |= 0x08;
				_output.buffer[7] |= 0x03;
				led_output(10, 1);
			}
			else
			{
				_output.buffer[6] &= 0xF7;
				_output.buffer[7] &= 0xFF;
				led_output(10, 0);
			}

			break;

		case 9:
			if(state == 1)
			{
				_output.buffer[6] |= 0x02;
				_output.buffer[7] |= 0x03;
				led_output(9, 1);
			}
			else
			{
				_output.buffer[6] &= 0xFD;
				_output.buffer[7] &= 0xFF;
				led_output(9, 0);
			}

			break;

		case 8:
			if(state == 1)
			{
				_output.buffer[6] |= 0x00;
				_output.buffer[7] |= 0x83;
				led_output(8, 1);
			}
			else
			{
				_output.buffer[6] &= 0xFF;
				_output.buffer[7] &= 0x7F;
				led_output(8, 0);
			}

			break;

		case 7:
			if(state == 1)
			{
				_output.buffer[6] |= 0x00;
				_output.buffer[7] |= 0x23;
				led_output(7, 1);
			}
			else
			{
				_output.buffer[6] &= 0xFF;
				_output.buffer[7] &= 0xDF;
				led_output(7, 0);
			}

			break;

		case 6:
			if(state == 1)
			{
				_output.buffer[6] |= 0x00;
				_output.buffer[7] |= 0x0B;
				led_output(6, 1);
			}
			else
			{
				_output.buffer[6] &= 0xFF;
				_output.buffer[7] &= 0xF7;
				led_output(6, 0);
			}

			break;

		case 5:
			if(state == 1)
			{
				_output.buffer[2] |= 0x20;
				_output.buffer[3] |= 0x03;
				led_output(5, 1);
			}
			else
			{
				_output.buffer[2] &= 0xDF;
				_output.buffer[3] &= 0xFF;
				led_output(5, 0);
			}

			break;

		case 4:
			if(state == 1)
			{
				_output.buffer[2] |= 0x08;
				_output.buffer[3] |= 0x03;
				led_output(4, 1);
			}
			else
			{
				_output.buffer[2] &= 0xF7;
				_output.buffer[3] &= 0xFF;
				led_output(4, 0);
			}

			break;

		case 3:
			if(state == 1)
			{
				_output.buffer[2] |= 0x02;
				_output.buffer[3] |= 0x03;
				led_output(3, 1);
			}
			else
			{
				_output.buffer[2] &= 0xFD;
				_output.buffer[3] &= 0xFF;
				led_output(3, 0);
			}

			break;

		case 2:
			if(state == 1)
			{
				_output.buffer[2] |= 0x00;
				_output.buffer[3] |= 0x83;
				led_output(2, 1);
			}
			else
			{
				_output.buffer[2] &= 0xFF;
				_output.buffer[3] &= 0x7F;
				led_output(2, 0);
			}

			break;

		case 1:
			if(state == 1)
			{
				_output.buffer[2] |= 0x00;
				_output.buffer[3] |= 0x23;
				led_output(1, 1);
			}
			else
			{
				_output.buffer[2] &= 0xFF;
				_output.buffer[3] &= 0xDF;
				led_output(1, 0);
			}

			break;

		case 0:
			if(state == 1)
			{

				_output.buffer[2] |= 0x00;
				_output.buffer[3] |= 0x0B;
				led_output(0, 1);
			}
			else
			{
				_output.buffer[2] &= 0xFF;
				_output.buffer[3] &= 0xF7;
				led_output(0, 0);
			}

			break;
	}



	T6819_cs(0);

	T6819_write(_output.buffer, 16);
	T6819_cs(1);
}
//t6826
/*void output_digitalWrite(int8_t line, int8_t state)
{
	switch(line)
	{
		case 0:
			if(state == 1)
			{
				_output.buffer[14] |= 0x02;
				led_output(0, 1);
			}
			else
			{
				_output.buffer[14] &= 0xFD;
				led_output(0, 0);
			}

			break;

		case 1:
			if(state == 1)
			{
				_output.buffer[14] |= 0x08;
				led_output(1, 1);
			}
			else
			{
				_output.buffer[14] &= 0xF7;
				led_output(1, 0);
			}

			break;

		case 2:
			if(state == 1)
			{
				_output.buffer[14] |= 0x20;
				led_output(2, 1);
			}
			else
			{
				_output.buffer[14] &= 0xDF;
				led_output(2, 0);
			}

			break;

		case 3:
			if(state == 1)
			{
				_output.buffer[12] |= 0x02;
				led_output(3, 1);
			}
			else
			{
				_output.buffer[12] &= 0xFD;
				led_output(3, 0);
			}

			break;

		case 4:
			if(state == 1)
			{
				_output.buffer[12] |= 0x08;
				led_output(4, 1);
			}
			else
			{
				_output.buffer[12] &= 0xF7;
				led_output(4, 0);
			}

			break;

		case 5:
			if(state == 1)
			{
				_output.buffer[12] |= 0x20;
				led_output(5, 1);
			}
			else
			{
				_output.buffer[12] &= 0xDF;
				led_output(5, 0);
			}

			break;

		case 6:
			if(state == 1)
			{
				_output.buffer[10] |= 0x02;
				led_output(6, 1);
			}
			else
			{
				_output.buffer[10] &= 0xFD;
				led_output(6, 0);
			}

			break;

		case 7:
			if(state == 1)
			{
				_output.buffer[10] |= 0x08;
				led_output(7, 1);
			}
			else
			{
				_output.buffer[10] &= 0xF7;
				led_output(7, 0);
			}

			break;

		case 8:
			if(state == 1)
			{
				_output.buffer[10] |= 0x20;
				led_output(8, 1);
			}
			else
			{
				_output.buffer[10] &= 0xDF;
				led_output(8, 0);
			}

			break;

		case 9:
			if(state == 1)
			{
				_output.buffer[8] |= 0x02;
				led_output(9, 1);
			}
			else
			{
				_output.buffer[8] &= 0xFD;
				led_output(9, 0);
			}

			break;

		case 10:
			if(state == 1)
			{
				_output.buffer[8] |= 0x08;
				led_output(10, 1);
			}
			else
			{
				_output.buffer[8] &= 0xF7;
				led_output(10, 0);
			}

			break;

		case 11:
			if(state == 1)
			{
				_output.buffer[8] |= 0x20;
				led_output(11, 1);
			}
			else
			{
				_output.buffer[8] &= 0xDF;
				led_output(11, 0);
			}

			break;

		case 12:
			if(state == 1)
			{
				_output.buffer[6] |= 0x02;
				led_output(12, 1);
			}
			else
			{
				_output.buffer[6] &= 0xFD;
				led_output(12, 0);
			}

			break;

		case 13:
			if(state == 1)
			{
				_output.buffer[6] |= 0x08;
				led_output(13, 1);
			}
			else
			{
				_output.buffer[6] &= 0xF7;
				led_output(13, 0);
			}

			break;

		case 14:
			if(state == 1)
			{
				_output.buffer[6] |= 0x20;
				led_output(14, 1);
			}
			else
			{
				_output.buffer[6] &= 0xDF;
				led_output(14, 0);
			}

			break;

		case 15:
			if(state == 1)
			{
				_output.buffer[4] |= 0x02;
				led_output(15, 1);
			}
			else
			{
				_output.buffer[4] &= 0xFD;
				led_output(15, 0);
			}

			break;

		case 16:
			if(state == 1)
			{
				_output.buffer[4] |= 0x08;
				led_output(16, 1);
			}
			else
			{
				_output.buffer[4] &= 0xF7;
				led_output(16, 0);
			}

			break;

		case 17:
			if(state == 1)
			{
				_output.buffer[4] |= 0x20;
				led_output(17, 1);
			}
			else
			{
				_output.buffer[4] &= 0xDF;
				led_output(17, 0);
			}

			break;

		case 18:
			if(state == 1)
			{
				_output.buffer[2] |= 0x02;
				led_output(18, 1);
			}
			else
			{
				_output.buffer[2] &= 0xFD;
				led_output(18, 0);
			}

			break;

		case 19:
			if(state == 1)
			{
				_output.buffer[2] |= 0x08;
				led_output(19, 1);
			}
			else
			{
				_output.buffer[2] &= 0xF7;
				led_output(19, 0);
			}

			break;

		case 20:
			if(state == 1)
			{
				_output.buffer[2] |= 0x20;
				led_output(20, 1);
			}
			else
			{
				_output.buffer[2] &= 0xDF;
				led_output(20, 0);
			}

			break;

		case 21:
			if(state == 1)
			{
				_output.buffer[0] |= 0x02;
				led_output(21, 1);
			}
			else
			{
				_output.buffer[0] &= 0xFD;
				led_output(21, 0);
			}

			break;

		case 22:
			if(state == 1)
			{
				_output.buffer[0] |= 0x08;
				led_output(22, 1);
			}
			else
			{
				_output.buffer[0] &= 0xF7;
				led_output(22, 0);
			}

			break;

		case 23:
			if(state == 1)
			{
				_output.buffer[0] |= 0x20;
				led_output(23, 1);
			}
			else
			{
				_output.buffer[0] &= 0xDF;
				led_output(23, 0);
			}

			break;
	}

	T6819_cs(0);
	T6819_write(_output.buffer, 16);
	T6819_cs(1);
}*/
