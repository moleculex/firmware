#include "output.h"
#include "motorDrive.h"

void motorDrive_control(char mode, int8_t rfr, int8_t di1, int8_t di2)
{
	switch(mode)
	{
		case OPEN:
			output_digitalWrite(rfr, 1);
			output_digitalWrite(di1, 1);
			output_digitalWrite(di2, 0);

			break;

		case CLOSE:
			output_digitalWrite(rfr, 1);
			output_digitalWrite(di1, 0);
			output_digitalWrite(di2, 1);

			break;

		case STOP:
			output_digitalWrite(rfr, 1);
			output_digitalWrite(di1, 0);
			output_digitalWrite(di2, 0);

			break;
	}
}
