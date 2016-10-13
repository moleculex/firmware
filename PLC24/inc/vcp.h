#ifndef __VCP_H
#define __VCP_H

#include "stm32f30x.h"


typedef struct{
	char buffer[128];
	char *buffer_ptr;
	char buffer_len;
}t_vcp;

t_vcp _vcp;

void vcp_init(void);
void vcp_reset_port(void);
char vcp_api(char *buffer);
void vcp_write(char *buffer, char length);
void vcp_read(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void USBWakeUp_IRQHandler(void);
void Get_SerialNum(void);
void Leave_LowPowerMode(void);

#endif
