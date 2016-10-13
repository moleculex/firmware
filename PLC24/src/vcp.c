#include "string.h"

#include "vcp.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_prop.h"
#include "usb_istr.h"

#include "platform_config.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_exti.h"
#include "stm32f30x_misc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

ErrorStatus HSEStartUpStatus;

static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);

void vcp_init(void)
{
	vcp_reset_port();//pull the USB D+ line low to disconnect the USB device from the PC
	vTaskDelay(500);//allow a few milliseconds before reconnecting

	_vcp.buffer_ptr = &_vcp.buffer[0];

	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef	EXTI_InitStructure;

	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Enable the SYSCFG module clock (used for the USB disconnect feature) */

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Enable the USB disconnect GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

	/* Enable the USB disconnect GPIO clock */
	//RCC_AHBPeriphClockCmd(VCP_DISCONNECT_RCC, ENABLE);

	/*Set PA11,12 as IN - USB_DM,DP*/

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/*SET PA11,12 for USB: USB_DM,DP*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_14);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_14);

	/* Configure the EXTI line 18 connected internally to the USB IP */
	EXTI_ClearITPendingBit(EXTI_Line18);
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; /*USB resume from suspend mode*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* USBCLK = PLLCLK = 48 MHz */
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

	/* Enable USB clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;

	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USB interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USB Wake-up interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USB_Init();
}

void vcp_reset_port(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);						//enable the AHB bus to use GPIOA

	/* Configure PA12 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;										//which pins to setup, seperated by |
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;									//setup for output mode
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;								//push-pull mode; also available is GPIO_OType_OD (open drain)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//update speed is 50Mhz; also available is GPIO_Speed_10MHz and GPIO_Speed_2MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;							//output not pulled up or down
	GPIO_Init(GPIOA, &GPIO_InitStructure);												//initialize GPIOA with the above structure

	GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_RESET);									//pull the USB BUS+ low to reset the bus
}

char vcp_api(char *buffer)
{
	char retVal = 0;

	vcp_read();
	vTaskDelay(100);
	if(buffer[0] == 'U')
	{
		vTaskDelay(100);
		retVal = 1;
	}

	return retVal;
}

void vcp_write (char *buffer, char length)
{
    UserToPMABufferCopy((unsigned char*)buffer, ENDP1_TXADDR, (uint16_t)length);
    SetEPTxCount(ENDP1, length);
    SetEPTxValid(ENDP1);
}

void vcp_read(void)
{
	SetEPRxValid(ENDP3);
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	USB_Istr();
}

void USBWakeUp_IRQHandler(void)
{
  /* Initiate external resume sequence (1 step) */
  Resume(RESUME_EXTERNAL);  
  EXTI_ClearITPendingBit(EXTI_Line18);
}

void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(uint32_t*)(0x1FFFF7AC);
  Device_Serial1 = *(uint32_t*)(0x1FFFF7B0);
  Device_Serial2 = *(uint32_t*)(0x1FFFF7B4);

  Device_Serial0 += Device_Serial2;

  if (Device_Serial0 != 0)
  {
    IntToUnicode (Device_Serial0, &Virtual_Com_Port_StringSerial[2] , 8);
    IntToUnicode (Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
  }
}

static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;

  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[ 2* idx + 1] = 0;
  }
}

void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();


  /* Wait till HSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {}

  /* Enable PLL1 */
  RCC_PLLCmd(ENABLE);

  /* Wait till PLL1 is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {}

  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  /* Wait till PLL is used as system clock source */
  while (RCC_GetSYSCLKSource() != 0x08)
  {}

 /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
}

