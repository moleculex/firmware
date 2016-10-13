#ifndef __MODEM_H
#define __MODEM_H

#include "buffer.h"
#include "string.h"
#include "stm32f30x.h"

#define MODEM_START_UP 0x00
#define MODEM_API 0x01
#define MODEM_IDLE 0x02

typedef enum{
	MODEM_UPSTREAM_STATUS,
	MODEM_UPSTREAM_ALARM,
	MODEM_UPSTREAM_RESPONSE,
	MODEM_UPSTREAM_IDLE
};

typedef struct{
	t_buffer rd_buffer;
	t_buffer wr_buffer;
	t_buffer temp_buffer;
	char modem;
	char appkey[32];
	char appeui[16];
	char deveui[16];
	char devaddr[8];
	char port[3];
	char port_length;
	char properties_stored;
	char state;
	char logon_count;
	struct{
		char state;
		struct{
			char sent;
			int timer;
		}status;
		struct{
			char sent;
			int timer;
		}alarm;
		struct{
			char sent;
			int timer;
		}response;
	}upstream;
}t_modem;

t_modem _modem;

void modem_radio_init(void);
void modem_mac_init(void);
void modem_startup(void);
void modem_manager(void);
void modem_send(t_buffer *buffer, size_t length);
void modem_write(t_buffer *buffer, char length);
void modem_radio_rx_0(void);
void modem_radio_set_wdt(char *period, size_t length);
void modem_mac_pause(void);
void modem_mac_resume(void);
void modem_mac_join(void);
void modem_prepare_packet(void);
void skeleton_key(void);

#endif
