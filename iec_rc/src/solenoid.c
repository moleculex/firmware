#include "platform_config.h"
#include "solenoid.h"
#include "led.h"
#include "buzzer.h"
#include "cfg.h"
#include "flash.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void solenoid_init(void);

void solenoid_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SOLENOID_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SOLENOID_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SOLENOID_PORT, &GPIO_InitStructure);
}

void solenoid_manager(void)
{
	solenoid_init();
	for(;;)
	{
		if(_solenoid.solenoid == 1)
		{
			flash_read(CFG_ROOT, _cfg.buffer, CFG_BUFFER_SIZE);
			if(_cfg.empty != 0x3C)
				cfg_default();
			else
				_cfg.solenoid_timeout = cfg_byteSwap(_cfg.solenoid_timeout);

			GPIO_SetBits(SOLENOID_PORT, SOLENOID_PIN);
			_led.sol_status = 1;
			buzzer_on();
			vTaskDelay(_cfg.solenoid_timeout);
			GPIO_ResetBits(SOLENOID_PORT, SOLENOID_PIN);
			_solenoid.solenoid = 0;
			_led.sol_status = 0;
			buzzer_off();
		}
		vTaskDelay(100);
	}
}
