#include "platform_config.h"
#include "sensors.h"
#include "led.h"
#include "stm32f30x_adc.h"
#include "stm32f30x_dma.h"
#include "stm32f30x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void sensors_init(void);

void sensors_init(void)
{
	_sensors.mains_presence = '0';
	_sensors.solenoid_presence = '0';
	_sensors.door_sensor_presence = '0';
	_sensors.vibration_sensor_presence = '0';
	_sensors.door_sensor = '0';
	_sensors.vibration_sensor = '0';

	_sensors.pending.mains_presence = '0';
	_sensors.pending.solenoid_presence = '0';
	_sensors.pending.door_sensor_presence = '0';
	_sensors.pending.vibration_sensor_presence = '0';
	_sensors.pending.door_sensor = '0';
	_sensors.pending.vibration_sensor = '0';

//DIGITAL
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(MAINS_PRESENCE_RCC | SOLENOID_PRESENCE_RCC | DOOR_SENSOR_PRESENCE_RCC | VIBRATION_SENSOR_PRESENCE_RCC | DOOR_SENSOR_RCC | VIBRATION_SENSOR_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = MAINS_PRESENCE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(MAINS_PRESENCE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SOLENOID_PRESENCE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SOLENOID_PRESENCE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DOOR_SENSOR_PRESENCE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DOOR_SENSOR_PRESENCE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = VIBRATION_SENSOR_PRESENCE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(VIBRATION_SENSOR_PRESENCE_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DOOR_SENSOR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DOOR_SENSOR_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = VIBRATION_SENSOR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(VIBRATION_SENSOR_PORT, &GPIO_InitStructure);
}

void sensors_manager(void)
{
	sensors_init();
	for(;;)
	{
		if(GPIO_ReadInputDataBit(MAINS_PRESENCE_PORT, MAINS_PRESENCE_PIN) == 1)
			_sensors.pending.mains_presence = 1;
		else
			_sensors.pending.mains_presence = 0;

		if(GPIO_ReadInputDataBit(SOLENOID_PRESENCE_PORT, SOLENOID_PRESENCE_PIN) == 0)
			_sensors.pending.solenoid_presence = 1;
		else
			_sensors.pending.solenoid_presence = 0;

		if(GPIO_ReadInputDataBit(DOOR_SENSOR_PRESENCE_PORT, DOOR_SENSOR_PRESENCE_PIN) == 0)
			_sensors.pending.door_sensor_presence = 1;
		else
			_sensors.pending.door_sensor_presence = 0;

		if(GPIO_ReadInputDataBit(VIBRATION_SENSOR_PRESENCE_PORT, VIBRATION_SENSOR_PRESENCE_PIN) == 0)
			_sensors.pending.vibration_sensor_presence = 1;
		else
			_sensors.pending.vibration_sensor_presence = 0;

		//Door open - Low
		if(GPIO_ReadInputDataBit(DOOR_SENSOR_PORT, DOOR_SENSOR_PIN) == 1)
			_sensors.pending.door_sensor = 1;
		else
			_sensors.pending.door_sensor = 0;

		if(GPIO_ReadInputDataBit(VIBRATION_SENSOR_PORT, VIBRATION_SENSOR_PIN) == 1)
			_sensors.pending.vibration_sensor = 1;
		else
			_sensors.pending.vibration_sensor = 0;

		vTaskDelay(100);

		if(GPIO_ReadInputDataBit(MAINS_PRESENCE_PORT, MAINS_PRESENCE_PIN) == 1 && _sensors.pending.mains_presence == 1)
		{
			_sensors.mains_presence = '1';
			_led.mains_presence = 1;
		}
		else
		{
			_sensors.mains_presence = '0';
			_led.mains_presence = 0;
		}

		if(GPIO_ReadInputDataBit(SOLENOID_PRESENCE_PORT, SOLENOID_PRESENCE_PIN) == 0 && _sensors.pending.solenoid_presence == 1)
			_sensors.solenoid_presence = '1';
		else
			_sensors.solenoid_presence = '0';

		if(GPIO_ReadInputDataBit(DOOR_SENSOR_PRESENCE_PORT, DOOR_SENSOR_PRESENCE_PIN) == 0 && _sensors.pending.door_sensor_presence == 1)
			_sensors.door_sensor_presence = '1';
		else
			_sensors.door_sensor_presence = '0';

		if(GPIO_ReadInputDataBit(VIBRATION_SENSOR_PRESENCE_PORT, VIBRATION_SENSOR_PRESENCE_PIN) == 0 && _sensors.pending.vibration_sensor_presence == 1)
			_sensors.vibration_sensor_presence = '1';
		else
			_sensors.vibration_sensor_presence = '0';

		if(GPIO_ReadInputDataBit(DOOR_SENSOR_PORT, DOOR_SENSOR_PIN) == 1 && _sensors.pending.door_sensor == 1)
		{
			_sensors.door_sensor = '0';
			_led.door_status = 1;
		}
		else
		{
			_sensors.door_sensor = '1';
			_led.door_status = 0;
		}

		if(GPIO_ReadInputDataBit(VIBRATION_SENSOR_PORT, VIBRATION_SENSOR_PIN) == 1 && _sensors.pending.vibration_sensor == 1)
		{
			_sensors.vibration_sensor = '1';
			_led.vib_status = 1;
		}
		else
		{
			_sensors.vibration_sensor = '0';
			_led.vib_status = 0;
		}

		vTaskDelay(100);
	}
}

/*void sensors_dma_init(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = ARRAYSIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

    DMA_Cmd(DMA1_Channel1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void sensors_adc_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    uint32_t calibration_value = 0;

    RCC_ADCCLKConfig(RCC_ADC12PLLCLK_OFF);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);


    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

	ADC_StructInit(&ADC_InitStructure);

	ADC_VoltageRegulatorCmd(ADC1, ENABLE);

	vTaskDelay(5);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Clock = ADC_Clock_SynClkModeDiv1;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
    ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);

	while(ADC_GetCalibrationStatus(ADC1) != RESET );

	calibration_value = ADC_GetCalibrationValue(ADC1);

	ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
	ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	ADC_InitStructure.ADC_NbrOfRegChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_601Cycles5);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_7Cycles5);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 3, ADC_SampleTime_7Cycles5);

    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY));

	ADC_StartConversion(ADC1);
}*/

