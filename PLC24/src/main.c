#include "app.h"
#include "vcp.h"
#include "platform_config.h"
#include "stm32f30x_iwdg.h"

#include "output.h"
#include "input.h"

#include "app.h"
#include "rotarySwitch.h"
#include "display.h"
#include "ir.h"
#include "trigger.h"
#include "proxySwitch.h"
#include "motorDrive.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define TASK_STACK_SIZE				( 256 )


int main(void)
{
	SysTick_Config(72000);

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(72000/32); //72000/32 = 1s
	IWDG_ReloadCounter();
	IWDG_Enable();

	//vcp_init();

	xSemaphore = xSemaphoreCreateMutex();

	xTaskCreate((pdTASK_CODE)app,
				(const signed char * const)"app",
				TASK_STACK_SIZE,
				NULL,
				2,
				NULL);

	xTaskCreate((pdTASK_CODE)app_display,
				(const signed char * const)"app_display",
				TASK_STACK_SIZE,
				NULL,
				4,
				NULL);

	xTaskCreate((pdTASK_CODE)app_ir,
				(const signed char * const)"app_ir",
				TASK_STACK_SIZE,
				NULL,
				3,
				NULL);

	xTaskCreate((pdTASK_CODE)app_rotarySwitch,
				(const signed char * const)"app_rotarySwitch",
				TASK_STACK_SIZE,
				NULL,
				4,
				NULL);

	xTaskCreate((pdTASK_CODE)app_trigger,
				(const signed char * const)"app_trigger",
				TASK_STACK_SIZE,
				NULL,
				4,
				NULL);

	xTaskCreate((pdTASK_CODE)app_motorDrive,
				(const signed char * const)"app_motorDrive",
				TASK_STACK_SIZE,
				NULL,
				2,
				NULL);

	vTaskStartScheduler();

	while(1);
}


