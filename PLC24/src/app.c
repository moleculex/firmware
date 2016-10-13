#include "string.h"

#include "stm32f30x_iwdg.h"

#include "app.h"

#include "rotarySwitch.h"
#include "display.h"
#include "ir.h"
#include "trigger.h"
#include "proxySwitch.h"
#include "motorDrive.h"
#include "led.h"
#include "output.h"
#include "input.h"

#include "platform_config.h"
#include "vcp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//LED outputs Blue- stand by green - opening red closing
//multiple trigger 5, stop tail gating
//buzzer
//power failure remain open flash cross
//seperate motor from brake by a few ms
//maintenance - after 6mnths leds flash red cross and beep for 10s every 30min, after 8mnths gate will open and stay open show red crosses

#include "T6819.h"
#include "_74HC595.h"
void app(void)
{
	_trigger.a = 0;
	_trigger.b = 0;
	int count = 0;
	char lock = 0;
	char direction = OPEN;
	char pwr_up = 1;
	char directionX = 0;
	_app.thread.motorDrive = OPEN;
	_app.thread.display = IDLE;

	for(int i = 0; i < 6; i++)
		_led.buffer[i] = 0;

	for(int i = 0; i < 16; i++)
		_output.buffer[i] = 0;

	input_digitalInit();

	_74HC595_init();
	T6819_init();


	for(;;)
	{
		if(_rotarySwitch.sw1 == 1)
			_app.thread.display = ENTRY_SIDE_A;

		if(_rotarySwitch.sw2 == 1)
			_app.thread.display = ENTRY_SIDE_B;

		if(_rotarySwitch.sw3 == 1)
			_app.thread.display = BI_DIRECTIONAL_ENTRY;

		if(_rotarySwitch.sw1 == 0 && _rotarySwitch.sw2 == 0 && _rotarySwitch.sw3 == 0)
		{
			_trigger.a = 0;
			_trigger.b = 0;
			_app.thread.display = NO_ENTRY;
		}

		if(_ir.a_int == 0 || _ir.b_int == 0 || _ir.crawl == 0)
		{
			_trigger.a = 0;
			_trigger.b = 0;
			_app.thread.display = OBSTRUCTION;
		}

		if(_trigger.a == 1 && (_rotarySwitch.sw1 == 1 || _rotarySwitch.sw3 == 1) && (_ir.a_int != 0 && _ir.b_int != 0 && _ir.crawl != 0))
		{
			_trigger.a = 0;
			if(lock == 0)
			{
				if(direction == STOP)
					lock = 0;
				else
					lock = 1;

				if(_ir.b_ext == 0)
				{
					app_display_fault(ENTRY_SIDE_A_FAULT);
				}
				else
				{
					count = 0;
					_app.thread.motorDrive = OPEN;
					direction = OPEN;
					directionX = 0;
				}
			}
		}

		if(_trigger.b == 1 && (_rotarySwitch.sw2 == 1 || _rotarySwitch.sw3 == 1) && (_ir.a_int != 0 && _ir.b_int != 0 && _ir.crawl != 0))
		{
			_trigger.b = 0;
			if(lock == 0)
			{
				if(direction == STOP)
					lock = 0;
				else
					lock = 1;

				if(_ir.a_ext == 0)
				{
					app_display_fault(ENTRY_SIDE_B_FAULT);
				}
				else
				{
					count = 0;
					_app.thread.motorDrive = OPEN;
					direction = OPEN;
					directionX = 1;
				}
			}
		}

		if(direction == OPEN)
		{
			if(proxySwitch_read(PROXY_SWITCH_MASTER_OPEN) == 1 && proxySwitch_read(PROXY_SWITCH_SLAVE_OPEN) == 1)
			{
				_app.thread.motorDrive = STOP;


				if(directionX == 0)
					_app.thread.display = ENTRY_SIDE_A_ACTIVE;

				if(directionX == 1)
					_app.thread.display = ENTRY_SIDE_B_ACTIVE;

				if(pwr_up == 1)
				{
					_app.thread.display = OBSTRUCTION;
				}

				if(count < 1000)
				{
					count++;

					if(directionX == 0)
					{
						if(_ir.b_ext == 0)
						{
							while(_ir.a_int == 0 || _ir.b_int == 0 || _ir.crawl == 0)
							{
								IWDG_ReloadCounter();
								vTaskDelay(100);
							}
							_app.thread.motorDrive = CLOSE;
							direction = CLOSE;
						}
					}

					if(directionX == 1)
					{
						if(_ir.a_ext == 0)
						{
							while(_ir.a_int == 0 || _ir.b_int == 0 || _ir.crawl == 0)
							{
								IWDG_ReloadCounter();
								vTaskDelay(100);
							}
							_app.thread.motorDrive = CLOSE;
							direction = CLOSE;
						}
					}
				}
				else
				{
					_app.thread.motorDrive = CLOSE;
					direction = CLOSE;
				}
			}
		}

		if(direction == CLOSE)
		{
			if(proxySwitch_read(PROXY_SWITCH_MASTER_CLOSED) == 1  && proxySwitch_read(PROXY_SWITCH_SLAVE_CLOSED) == 1)
			{
				lock = 0;
				_app.thread.motorDrive = STOP;
				direction = STOP;
			}

			if(_ir.a_int == 0 || _ir.b_int == 0 || _ir.crawl == 0)
			{
				if(proxySwitch_read(PROXY_SWITCH_MASTER_OPEN) != 1 && proxySwitch_read(PROXY_SWITCH_SLAVE_OPEN) != 1)
				{
					count = 0;
					_app.thread.motorDrive = OPEN;
					direction = OPEN;
				}
			}
		}

		if(direction == STOP)
		{
			if(proxySwitch_read(PROXY_SWITCH_MASTER_CLOSED) != 1 && proxySwitch_read(PROXY_SWITCH_SLAVE_CLOSED) != 1)
			{
				_app.thread.motorDrive = CLOSE;
				direction = CLOSE;
			}
		}

		vTaskDelay(10);
	}
}

void app_display(void)
{
	for(;;)
	{
		if(xSemaphoreTake(xSemaphore, 100) == pdTRUE)
		{
			switch(_app.thread.display)
			{
				case IDLE:
					break;

				case ENTRY_SIDE_A:
					display_show(DISPLAY_A_ARROW_RIGHT, 1);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT,0);
					display_show(DISPLAY_B_CROSS, 1);

					break;

				case ENTRY_SIDE_B:
					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 1);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 1);
					display_show(DISPLAY_B_CROSS, 0);

					break;

				case BI_DIRECTIONAL_ENTRY:
					display_show(DISPLAY_A_ARROW_RIGHT, 1);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 1);
					display_show(DISPLAY_B_CROSS, 0);

					break;

				case NO_ENTRY:
					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 1);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 0);
					display_show(DISPLAY_B_CROSS, 1);

					break;

				case ENTRY_SIDE_A_ACTIVE:
					display_show(DISPLAY_A_ARROW_RIGHT, 1);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 1);
					display_show(DISPLAY_B_ARROW_LEFT, 0);
					display_show(DISPLAY_B_CROSS, 0);

					vTaskDelay(500);

					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 0);
					display_show(DISPLAY_B_CROSS, 0);

					break;

				case ENTRY_SIDE_B_ACTIVE:
					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 1);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 1);
					display_show(DISPLAY_B_CROSS, 0);

					vTaskDelay(500);

					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 0);
					display_show(DISPLAY_B_CROSS, 0);

					break;

				case OBSTRUCTION:
					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 1);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 0);
					display_show(DISPLAY_B_CROSS, 1);

					vTaskDelay(500);

					display_show(DISPLAY_A_ARROW_RIGHT, 0);
					display_show(DISPLAY_A_ARROW_LEFT, 0);
					display_show(DISPLAY_A_CROSS, 0);
					display_show(DISPLAY_B_ARROW_RIGHT, 0);
					display_show(DISPLAY_B_ARROW_LEFT, 0);
					display_show(DISPLAY_B_CROSS, 0);

					break;
			}
			xSemaphoreGive(xSemaphore);
		}
		vTaskDelay(500);
	}
}

void app_display_fault(char fault)
{
	if(xSemaphoreTake(xSemaphore, 100) == pdTRUE)
	{
		if(fault == ENTRY_SIDE_A_FAULT)
		{
			display_show(DISPLAY_A_ARROW_RIGHT, 0);
			display_show(DISPLAY_A_ARROW_LEFT, 0);
			display_show(DISPLAY_A_CROSS, 1);
			display_show(DISPLAY_B_ARROW_RIGHT, 0);

			if(_app.thread.display == BI_DIRECTIONAL_ENTRY)
			{
				display_show(DISPLAY_B_ARROW_LEFT, 1);
				display_show(DISPLAY_B_CROSS, 0);

			}
			else
			{
				display_show(DISPLAY_B_ARROW_LEFT, 0);
				display_show(DISPLAY_B_CROSS, 1);
			}
		}

		if(fault == ENTRY_SIDE_B_FAULT)
		{
			if(_app.thread.display == BI_DIRECTIONAL_ENTRY)
			{
				display_show(DISPLAY_A_ARROW_RIGHT, 1);
				display_show(DISPLAY_A_CROSS, 0);
			}
			else
			{
				display_show(DISPLAY_A_ARROW_RIGHT, 0);
				display_show(DISPLAY_A_CROSS, 1);
			}
			display_show(DISPLAY_A_ARROW_LEFT, 0);
			display_show(DISPLAY_B_ARROW_RIGHT, 0);
			display_show(DISPLAY_B_ARROW_LEFT, 0);
			display_show(DISPLAY_B_CROSS, 1);
		}

		vTaskDelay(500);
		xSemaphoreGive(xSemaphore);
	}
}

void app_ir(void)
{
	for(;;)
	{
		_ir.b_ext = (char)ir_rx(IR_RX_B_EXT);
		_ir.b_int = (char)ir_rx(IR_RX_B_INT);
		_ir.a_int = (char)ir_rx(IR_RX_A_INT);
		_ir.a_ext = (char)ir_rx(IR_RX_A_EXT);
		_ir.crawl = (char)ir_rx(IR_RX_CRAWL);

		vTaskDelay(10);
	}
}

void app_rotarySwitch(void)
{
	for(;;)
	{
		_rotarySwitch.sw1 = (char)rotarySwitch_read(SW_1);
		_rotarySwitch.sw2 = (char)rotarySwitch_read(SW_2);
		_rotarySwitch.sw3 = (char)rotarySwitch_read(SW_3);

		vTaskDelay(500);
	}
}


void app_trigger(void)
{
	char tmpA;
	char tmpB;

	for(;;)
	{
		tmpA = 0;
		tmpB = 0;

		if(trigger_read(TRIGGER_A) == 1)
			tmpA = 1;

		if(trigger_read(TRIGGER_B) == 1)
			tmpB = 1;

		vTaskDelay(20);

		if(trigger_read(TRIGGER_A) == 1 && tmpA == 1)
		{
			_trigger.a = 1;
			if(_trigger.a_cnt_en == 1)
			{
				_trigger.a_cnt++;
			}
		}

		if(trigger_read(TRIGGER_B) == 1 && tmpB == 1)
		{
			_trigger.b = 1;
			if(_trigger.b_cnt_en == 1)
			{
				_trigger.b_cnt++;
			}
		}

		vTaskDelay(100);
	}
}

void app_motorDrive(void)
{
	for(;;)
	{
		switch(_app.thread.motorDrive)
		{
			case STOP:
				motorDrive_control(STOP, RFR, DI_1, DI_2);
				vTaskDelay(200);
				output_digitalWrite(BRAKE, 1);
				break;

			case OPEN:
				output_digitalWrite(BRAKE, 0);
				vTaskDelay(200);
				motorDrive_control(OPEN, RFR, DI_1, DI_2);
				break;

			case CLOSE:
				output_digitalWrite(BRAKE, 0);
				vTaskDelay(200);
				motorDrive_control(CLOSE, RFR, DI_1, DI_2);
				break;

		}

		IWDG_ReloadCounter();
		vTaskDelay(10);
	}
}
