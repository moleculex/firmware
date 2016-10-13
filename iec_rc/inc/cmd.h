#ifndef __CMD_H
#define __CMD_H

#include "cfg.h"

#define CMD_ERASE	0xF0
#define CMD_WRITE	0xF1
#define CMD_READ	0xF2

typedef enum{
	CMD_SRC_MODEM,
	CMD_SRC_USB
};

typedef enum{
	CMD_FLASH_CONFIG = 0xA0,
	CMD_OUTPUT_SOLENOID,
	CMD_OUTPUT_BUZZER,
	CMD_APP_SOLENOID,
	CMD_STATUS
};


#define CMD_FLASH_CONFIG_WRITE		0xD1
#define CMD_FLASH_CONFIG_READ		0xD2
#define CMD_STATUS_READ				0xE2

#define CMD_BUFFER_SIZE 64

//|erw|id|len|payload|

typedef struct
{
	union
	{
		char buffer[CMD_BUFFER_SIZE];
		struct
		{
			unsigned char erw;
			unsigned char id;
			char len;
			union
			{
				char payload[CMD_BUFFER_SIZE];
				struct
				{
					char state;
					char reserved[63];
				}__attribute__((packed)) solenoid;
				struct
				{
					char state;
					char reserved[63];
				}__attribute__((packed)) buzzer;
				struct
				{
					t_cfg cfg;
					char reserved[56];
				}__attribute__((packed)) config;
			};
		}__attribute__((packed));
	};
	char src;
}t_cmd;

t_cmd _cmd;

void cmd_process(void);

#endif
