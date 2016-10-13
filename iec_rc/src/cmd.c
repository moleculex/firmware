#include "cfg.h"
#include "cmd.h"
#include "flash.h"
#include "solenoid.h"
#include "led.h"
#include "platform_config.h"
#include "string.h"
#include "modem.h"
#include "vcp.h"
#include "pkt.h"
#include "monitor.h"
#include "battery.h"
#include "solenoid.h"

void cmd_erase(void);
void cmd_write(void);
void cmd_read(void);

// rw|id|

// 0xAX - Flash - X=0 Erase, X=1 Write, X=2 Read
/*
 * addr[3]|addr[2]|addr[1]|addr[0]|len[1]|len[0]| *data|
 */

// 0xBX - Outputs Atomic, X=0 Solenoid, X=1 Buzzer
/*
 * |state|
 */

// 0xCX - Inputs Atomic, X=0 Vibration, X=1 Door
/*
 * |state|
 */

// 0xDX - Config, X=0 Erase, X=1 Write, X=2 Read
/*
 * | CFG_EMPTY |
 *   CFG_ALARM_RESET_INTERVAL[1] | CFG_ALARM_RESET_INTERVAL[0] |
 *   CFG_STATUS_INTERVAL[1] | CFG_STATUS_INTERVAL[0] |
 *   CFG_ALARMS_IN_USE |
 */

// 0xEX - App , X=0 Status, X=1 Solenoid with timeout
/*
 *
 */

void cmd_process(void)
{
	switch(_cmd.erw)
	{
		case CMD_ERASE:
			cmd_erase();
			break;

		case CMD_READ:
			cmd_read();
			break;

		case CMD_WRITE:
			cmd_write();
			break;
	}

//	switch(_cmd.id)
//	{
		/*case 0xA0:
			int n = 3;
			for(int i = 0; i < 4; i++)
				_flash.address_8bit[i] = c.buffer[1 + (n - i)];

			flash_read(_flash.address_32bit, _flash.buffer, 1024);
			flash_erase(1024 * _flash.address_32bit/1024);

			break;*/

		/*case 0xA1:
			int n = 3;
			for(int i = 0; i < 4; i++)
				_flash.address_8bit[i] = c.buffer[1 + (n - i)];

			flash_read(_flash.address_32bit, _flash.buffer, 1024);
			flash_erase(1024 * _flash.address_32bit/1024);
			flash_write(_flash.address_32bit, _flash.buffer, 1024);

			break;*/

		/*case 0xA2:
			int n = 3;
			for(int i = 0; i < 4; i++)
				_flash.address_8bit[i] = c.buffer[1 + (n - i)];

			flash_read(_flash.address_32bit, &c.buffer[6], (int)c.buffer[5]);

			break;*/

}

void cmd_erase(void)
{
	switch(_cmd.id)
	{
		case CMD_FLASH_CONFIG:
			flash_erase(CFG_ROOT);

			break;
	}
}

void cmd_write(void)
{
	switch(_cmd.id)
	{
		case CMD_OUTPUT_SOLENOID:
			if(_cmd.solenoid.state == 0x00)
			{
				GPIO_ResetBits(SOLENOID_PORT, SOLENOID_PIN);
				GPIO_SetBits(LED_SOLENOID_PORT, LED_SOLENOID_PIN);
			}
			else
			{
				if(_cmd.solenoid.state == 0x01)
				{
					GPIO_SetBits(SOLENOID_PORT, SOLENOID_PIN);
					GPIO_ResetBits(LED_SOLENOID_PORT, LED_SOLENOID_PIN);
				}
			}

			break;

		case CMD_OUTPUT_BUZZER:
			if(_cmd.buzzer.state == 0x00)
			{
				GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
			}
			else
			{
				if(_cmd.buzzer.state == 0x01)
				{
					GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
				}
			}

			break;

		case CMD_FLASH_CONFIG:
			flash_erase(CFG_ROOT);
			_cfg.empty = 0x3C;
			memcpy(&_cfg.buffer[1], &_cmd.payload, CFG_BUFFER_SIZE - 1);
			flash_write(CFG_ROOT, _cfg.buffer, CFG_BUFFER_SIZE);

			break;

		case CMD_APP_SOLENOID:
			_solenoid.solenoid = 1;

			break;
	}
}

void cmd_read(void)
{
	switch(_cmd.id)
	{
		case CMD_FLASH_CONFIG:
			flash_read(CFG_ROOT, _flash.buffer, CFG_BUFFER_SIZE);
			if(_cmd.src == CMD_SRC_MODEM)
			{
				hex_to_hexStr((char *)CMD_READ, &_modem.temp_buffer.data[0], 1);
				hex_to_hexStr((char *)CMD_FLASH_CONFIG, &_modem.temp_buffer.data[2], 1);
				hex_to_hexStr((char *)(6 + (CFG_BUFFER_SIZE - 1)*2), &_modem.temp_buffer.data[4], 1);
				hex_to_hexStr(&_flash.buffer[1], &_modem.temp_buffer.data[6], CFG_BUFFER_SIZE - 1);
				_modem.temp_buffer.count = 6 + (CFG_BUFFER_SIZE - 1)*2;
				_modem.upstream.state = MODEM_UPSTREAM_RESPONSE;
			}
			else
			{
				hex_to_hexStr((char *)CMD_READ, &_vcp.wr_buffer.data[0], 1);
				hex_to_hexStr((char *)CMD_FLASH_CONFIG, &_vcp.wr_buffer.data[2], 1);
				hex_to_hexStr((char *)(6 + (CFG_BUFFER_SIZE - 1)*2), &_vcp.wr_buffer.data[4], 1);
				hex_to_hexStr(&_flash.buffer[1], &_vcp.wr_buffer.data[6], CFG_BUFFER_SIZE - 1);

				vcp_write(&_vcp.wr_buffer, 6 + (CFG_BUFFER_SIZE - 1)*2);
			}
			break;

		case CMD_STATUS:
			if(_cmd.src == CMD_SRC_MODEM)
			{
				hex_to_hexStr((char *)CMD_READ, &_modem.temp_buffer.data[0], 1);
				hex_to_hexStr((char *)CMD_FLASH_CONFIG, &_modem.temp_buffer.data[2], 1);
				hex_to_hexStr((char *)(6 + 14), &_modem.temp_buffer.data[4], 1);
				_modem.temp_buffer.data[6] = _monitor.mains_presence;
				_modem.temp_buffer.data[7] = _monitor.solenoid_presence;
				_modem.temp_buffer.data[8] = _monitor.door_sensor_presence;
				_modem.temp_buffer.data[9] = _monitor.vibration_sensor_presence;
				_modem.temp_buffer.data[10] = _modem.modem;
				_modem.temp_buffer.data[11] = '0';
				_modem.temp_buffer.data[12] = _monitor.door_sensor;
				_modem.temp_buffer.data[13] = _monitor.vibration_sensor;
				_monitor.vibration_sensor = '0';
				_modem.temp_buffer.data[14] = '0';
				_modem.temp_buffer.data[15] = _battery.strLevel[0];
				_modem.temp_buffer.data[16] = _battery.strLevel[1];
				_modem.temp_buffer.data[17] = _battery.strLevel[2];
				_modem.temp_buffer.data[18] = _battery.strLevel[3];
				_modem.temp_buffer.data[19] = _monitor.battery_status;

				_modem.temp_buffer.count = 6 + 14;
				_modem.upstream.state = MODEM_UPSTREAM_RESPONSE;
			}
			else
			{
				hex_to_hexStr((char *)CMD_READ, &_vcp.wr_buffer.data[0], 1);
				hex_to_hexStr((char *)CMD_FLASH_CONFIG, &_vcp.wr_buffer.data[2], 1);
				hex_to_hexStr((char *)(6 + 14), &_vcp.wr_buffer.data[4], 1);
				_vcp.wr_buffer.data[6] = _monitor.mains_presence;
				_vcp.wr_buffer.data[7] = _monitor.solenoid_presence;
				_vcp.wr_buffer.data[8] = _monitor.door_sensor_presence;
				_vcp.wr_buffer.data[9] = _monitor.vibration_sensor_presence;
				_vcp.wr_buffer.data[10] = _modem.modem;
				_vcp.wr_buffer.data[11] = '0';
				_vcp.wr_buffer.data[12] = _monitor.door_sensor;
				_vcp.wr_buffer.data[13] = _monitor.vibration_sensor;
				_monitor.vibration_sensor = '0';
				_vcp.wr_buffer.data[14] = '0';
				_vcp.wr_buffer.data[15] = _battery.strLevel[0];
				_vcp.wr_buffer.data[16] = _battery.strLevel[1];
				_vcp.wr_buffer.data[17] = _battery.strLevel[2];
				_vcp.wr_buffer.data[18] = _battery.strLevel[3];
				_vcp.wr_buffer.data[19] = _monitor.battery_status;

				vcp_write(&_vcp.wr_buffer, 6 + 14);
			}

			break;
	}
}
