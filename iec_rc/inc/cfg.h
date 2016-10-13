#ifndef __CFG_H
#define __CFG_H

#include "stm32f30x.h"

#define CFG_ROOT 							0x0800FA00

#define CFG_BUFFER_SIZE						(int)8

typedef struct
{
	union
	{
		char buffer[CFG_BUFFER_SIZE];
		struct
		{
			char empty;
			uint16_t alarm_reset_interval;
			uint16_t alarm_status_interval;
			uint16_t solenoid_timeout;
			union
			{
				char alarms;
				struct
				{
					unsigned door_sensor:1;
					unsigned door_sensor_presence:1;
					unsigned vibration_sensor:1;
					unsigned vibration_sensor_presence:1;
					unsigned solenoid_presence:1;
					unsigned battery_status:1;
					unsigned reserved:2;
				};
			}alarms_in_use;
		}__attribute__((packed));
	};
}t_cfg;

t_cfg _cfg;

void cfg_default(void);
uint16_t cfg_byteSwap(uint16_t val);

#endif
