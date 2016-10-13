#ifndef __MONITOR_H
#define __MONITOR_H

#include "stm32f30x_gpio.h"

#define DEVICE_TYPE_SOLENOID 0x01
#define DEVICE_TYPE_VIB_SENSOR 0x02
#define DEVICE_TYPE_DOOR_SENSOR 0x03

typedef struct{
	uint16_t input_val[4];
	uint16_t int_input_val[4];
	GPIO_TypeDef* vib_port;
	GPIO_TypeDef* door_port;
	uint16_t vib_pin;
	uint16_t door_pin;
	char mains_presence;
	char solenoid_presence;
	char door_sensor_presence;
	char vibration_sensor_presence;
	char door_sensor;
	char vibration_sensor;
	char vibration_sensor_count;
	char battery_status;
	struct{
		char mains_presence;
		char solenoid_presence;
		char door_sensor_presence;
		char vibration_sensor_presence;
		char door_sensor;
		char vibration_sensor;
	}pending;
}t_monitor;

typedef struct{
	char type;
	char previous_type;
	uint16_t id;
	GPIO_TypeDef* port;
	uint16_t pin;
}t_device;

t_monitor _monitor;
t_device _device[3];

void monitor_manager(void);

#endif
