#include "T6819.h"
#include "platform_config.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
void T6819_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	/* Enable the SPI periph */
	RCC_APB1PeriphClockCmd(SPIy_CLK, ENABLE);

	/* Enable SCK, MOSI, MISO and CS GPIO clocks */
	RCC_AHBPeriphClockCmd(SPIy_SCK_GPIO_CLK | SPIy_MISO_GPIO_CLK | SPIy_MOSI_GPIO_CLK | SPIy_CS_GPIO_CLK , ENABLE);

	GPIO_PinAFConfig(SPIy_SCK_GPIO_PORT, SPIy_SCK_SOURCE, SPIy_SCK_AF);
	GPIO_PinAFConfig(SPIy_MOSI_GPIO_PORT, SPIy_MOSI_SOURCE, SPIy_MOSI_AF);
	GPIO_PinAFConfig(SPIy_MISO_GPIO_PORT, SPIy_MISO_SOURCE, SPIy_MISO_AF);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = SPIy_SCK_PIN;
	GPIO_Init(SPIy_SCK_GPIO_PORT, &GPIO_InitStructure);

	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  SPIy_MOSI_PIN;
	GPIO_Init(SPIy_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/* SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = SPIy_MISO_PIN;
	GPIO_Init(SPIy_MISO_GPIO_PORT, &GPIO_InitStructure);

	/* SPI configuration -------------------------------------------------------*/
	SPI_I2S_DeInit(SPIy);
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPIy, &SPI_InitStructure);


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = SPIy_CS_PIN;
	GPIO_Init(SPIy_CS_GPIO_PORT, &GPIO_InitStructure);

	/* Enable the SPI peripheral */
	SPI_Cmd(SPIy, ENABLE);
}

void T6819_write(char *buffer, int length)
{
	for(int i = 0; i < length; i++)
	{
		SPI_SendData8(SPIy, buffer[i]);
		while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);
		while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);
	}
}

void T6819_cs(char state)
{
	if(state == 1)
		GPIO_SetBits(SPIy_CS_GPIO_PORT, SPIy_CS_PIN);
	else
		GPIO_ResetBits(SPIy_CS_GPIO_PORT, SPIy_CS_PIN);
}
