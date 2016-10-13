#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#include "stm32f30x.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_spi.h"

//INPUT
#define X0_RCC		RCC_AHBPeriph_GPIOD
#define X0_PORT 	GPIOD
#define X0_PIN	 	GPIO_Pin_13

#define X1_RCC		RCC_AHBPeriph_GPIOD
#define X1_PORT 	GPIOD
#define X1_PIN	 	GPIO_Pin_12

#define X2_RCC		RCC_AHBPeriph_GPIOB
#define X2_PORT 	GPIOB
#define X2_PIN	 	GPIO_Pin_0

#define X3_RCC		RCC_AHBPeriph_GPIOB
#define X3_PORT 	GPIOB
#define X3_PIN	 	GPIO_Pin_1

#define X4_RCC		RCC_AHBPeriph_GPIOE
#define X4_PORT 	GPIOE
#define X4_PIN	 	GPIO_Pin_10

#define X5_RCC		RCC_AHBPeriph_GPIOB
#define X5_PORT 	GPIOB
#define X5_PIN	 	GPIO_Pin_2

#define X6_RCC		RCC_AHBPeriph_GPIOE
#define X6_PORT 	GPIOE
#define X6_PIN	 	GPIO_Pin_7

#define X7_RCC		RCC_AHBPeriph_GPIOC
#define X7_PORT 	GPIOC
#define X7_PIN	 	GPIO_Pin_5

#define X8_RCC		RCC_AHBPeriph_GPIOC
#define X8_PORT 	GPIOC
#define X8_PIN	 	GPIO_Pin_4

#define X9_RCC		RCC_AHBPeriph_GPIOA
#define X9_PORT 	GPIOA
#define X9_PIN	 	GPIO_Pin_7

#define X10_RCC		RCC_AHBPeriph_GPIOD
#define X10_PORT 	GPIOD
#define X10_PIN	 	GPIO_Pin_6

#define X11_RCC		RCC_AHBPeriph_GPIOD
#define X11_PORT 	GPIOD
#define X11_PIN	 	GPIO_Pin_5

#define X12_RCC		RCC_AHBPeriph_GPIOD
#define X12_PORT 	GPIOD
#define X12_PIN	 	GPIO_Pin_4

#define X13_RCC		RCC_AHBPeriph_GPIOD
#define X13_PORT 	GPIOD
#define X13_PIN	 	GPIO_Pin_3

#define X14_RCC		RCC_AHBPeriph_GPIOE
#define X14_PORT 	GPIOE
#define X14_PIN	 	GPIO_Pin_5

#define X15_RCC		RCC_AHBPeriph_GPIOE
#define X15_PORT 	GPIOE
#define X15_PIN	 	GPIO_Pin_6

#define X16_RCC		RCC_AHBPeriph_GPIOA
#define X16_PORT 	GPIOA
#define X16_PIN	 	GPIO_Pin_6

#define X17_RCC		RCC_AHBPeriph_GPIOA
#define X17_PORT 	GPIOA
#define X17_PIN	 	GPIO_Pin_5

#define X18_RCC		RCC_AHBPeriph_GPIOA
#define X18_PORT 	GPIOA
#define X18_PIN	 	GPIO_Pin_4

#define X19_RCC		RCC_AHBPeriph_GPIOC
#define X19_PORT 	GPIOC
#define X19_PIN	 	GPIO_Pin_2

#define X20_RCC		RCC_AHBPeriph_GPIOC
#define X20_PORT 	GPIOC
#define X20_PIN	 	GPIO_Pin_1

#define X21_RCC		RCC_AHBPeriph_GPIOF
#define X21_PORT 	GPIOF
#define X21_PIN	 	GPIO_Pin_2

#define X22_RCC		RCC_AHBPeriph_GPIOC
#define X22_PORT 	GPIOC
#define X22_PIN	 	GPIO_Pin_3

#define X23_RCC		RCC_AHBPeriph_GPIOC
#define X23_PORT 	GPIOC
#define X23_PIN	 	GPIO_Pin_0

//DA
#define D_A_SEL0_RCC		RCC_AHBPeriph_GPIOA
#define D_A_SEL0_PORT 		GPIOA
#define D_A_SEL0_PIN	 	GPIO_Pin_0

#define D_A_SEL1_RCC		RCC_AHBPeriph_GPIOE
#define D_A_SEL1_PORT 		GPIOE
#define D_A_SEL1_PIN	 	GPIO_Pin_8

#define D_A_SEL2_RCC		RCC_AHBPeriph_GPIOD
#define D_A_SEL2_PORT 		GPIOD
#define D_A_SEL2_PIN	 	GPIO_Pin_8

#define D_A_SEL3_RCC		RCC_AHBPeriph_GPIOD
#define D_A_SEL3_PORT 		GPIOD
#define D_A_SEL3_PIN	 	GPIO_Pin_9

#define D_A_SEL4_RCC		RCC_AHBPeriph_GPIOD
#define D_A_SEL4_PORT 		GPIOD
#define D_A_SEL4_PIN	 	GPIO_Pin_10

#define D_A_SEL5_RCC		RCC_AHBPeriph_GPIOD
#define D_A_SEL5_PORT 		GPIOD
#define D_A_SEL5_PIN	 	GPIO_Pin_11

#define D_A_SEL6_RCC		RCC_AHBPeriph_GPIOD
#define D_A_SEL6_PORT 		GPIOD
#define D_A_SEL6_PIN	 	GPIO_Pin_14

#define D_A_SEL7_RCC		RCC_AHBPeriph_GPIOD
#define D_A_SEL7_PORT 		GPIOD
#define D_A_SEL7_PIN	 	GPIO_Pin_15

//CV
#define C_V_SEL0_RCC		RCC_AHBPeriph_GPIOF
#define C_V_SEL0_PORT 		GPIOF
#define C_V_SEL0_PIN	 	GPIO_Pin_6

#define C_V_SEL1_RCC		RCC_AHBPeriph_GPIOD
#define C_V_SEL1_PORT 		GPIOD
#define C_V_SEL1_PIN	 	GPIO_Pin_0

#define C_V_SEL2_RCC		RCC_AHBPeriph_GPIOD
#define C_V_SEL2_PORT 		GPIOD
#define C_V_SEL2_PIN	 	GPIO_Pin_1

#define C_V_SEL3_RCC		RCC_AHBPeriph_GPIOD
#define C_V_SEL3_PORT 		GPIOD
#define C_V_SEL3_PIN	 	GPIO_Pin_2

#define C_V_SEL4_RCC		RCC_AHBPeriph_GPIOD
#define C_V_SEL4_PORT 		GPIOD
#define C_V_SEL4_PIN	 	GPIO_Pin_7

#define C_V_SEL5_RCC		RCC_AHBPeriph_GPIOB
#define C_V_SEL5_PORT 		GPIOB
#define C_V_SEL5_PIN	 	GPIO_Pin_8

#define C_V_SEL6_RCC		RCC_AHBPeriph_GPIOB
#define C_V_SEL6_PORT 		GPIOB
#define C_V_SEL6_PIN	 	GPIO_Pin_5

#define C_V_SEL7_RCC		RCC_AHBPeriph_GPIOB
#define C_V_SEL7_PORT 		GPIOB
#define C_V_SEL7_PIN	 	GPIO_Pin_9

//LED
/*#define LED_INPUT0_PORT 	GPIOE
#define LED_INPUT0_PIN	 	GPIO_Pin_14

#define LED_INPUT1_PORT 	GPIOB
#define LED_INPUT1_PIN	 	GPIO_Pin_2

#define LED_INPUT2_PORT 	GPIOE
#define LED_INPUT2_PIN	 	GPIO_Pin_7

#define LED_INPUT3_PORT 	GPIOC
#define LED_INPUT3_PIN	 	GPIO_Pin_5

#define LED_INPUT4_PORT 	GPIOC
#define LED_INPUT4_PIN	 	GPIO_Pin_4

#define LED_INPUT5_PORT 	GPIOA
#define LED_INPUT5_PIN	 	GPIO_Pin_7

#define LED_INPUT6_PORT 	GPIOE
#define LED_INPUT6_PIN	 	GPIO_Pin_6

#define LED_INPUT7_PORT 	GPIOE
#define LED_INPUT7_PIN	 	GPIO_Pin_5*/

//PLC 0
//INPUT
//ROTARY_SWITCH
#define	SW_1	0
#define	SW_2	1
#define	SW_3	2

//IR
#define	IR_RX_B_EXT		3
#define	IR_RX_A_EXT		4
#define	IR_RX_B_INT		5
#define	IR_RX_A_INT		6
#define	IR_RX_CRAWL		7

//OUTPUT
//DISPLAY
#define	DISPLAY_A_ARROW_LEFT 	0
#define	DISPLAY_A_CROSS			1
#define	DISPLAY_A_ARROW_RIGHT 	2
#define	DISPLAY_B_ARROW_LEFT	3
#define	DISPLAY_B_CROSS			4
#define	DISPLAY_B_ARROW_RIGHT	5


//PLC 1
//INPUT
//PROXY_SWITCH
#define	PROXY_SWITCH_SLAVE_CLOSED		8//0
#define	PROXY_SWITCH_SLAVE_OPEN			9//1
#define	PROXY_SWITCH_MASTER_CLOSED		10//2
#define	PROXY_SWITCH_MASTER_OPEN		11//3

//TRIGGER
#define	TRIGGER_FIRE			12//4
#define	TRIGGER_RECEPTION 		13//5
#define	TRIGGER_A				14//6
#define	TRIGGER_B 				15//7

//OUTPUT
//MOTOR_DRIVE
#define RFR 	6//0	//YELLOW
#define DI_1 	7//1	//PURPLE
#define	DI_2 	8//2	//GREEN
#define DI_4 	9//6	//GREY
//#define DI_3 	10//3	//GREY
#define BRAKE 	10

//SPI LEDs
#define SPIx                             SPI2
#define SPIx_CLK                         RCC_APB1Periph_SPI2
#define SPIx_IRQn                        SPI2_IRQn

#define SPIx_SCK_PIN                     GPIO_Pin_13
#define SPIx_SCK_GPIO_PORT               GPIOB
#define SPIx_SCK_GPIO_CLK                RCC_AHBPeriph_GPIOB
#define SPIx_SCK_SOURCE                  GPIO_PinSource13
#define SPIx_SCK_AF                      GPIO_AF_5

#define SPIx_MISO_PIN                    GPIO_Pin_14
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define SPIx_MISO_SOURCE                 GPIO_PinSource14
#define SPIx_MISO_AF                     GPIO_AF_5

#define SPIx_MOSI_PIN                    GPIO_Pin_15
#define SPIx_MOSI_GPIO_PORT              GPIOB
#define SPIx_MOSI_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define SPIx_MOSI_SOURCE                 GPIO_PinSource15
#define SPIx_MOSI_AF                     GPIO_AF_5

#define SPIx_CS_PIN                      GPIO_Pin_12
#define SPIx_CS_GPIO_PORT                GPIOB
#define SPIx_CS_GPIO_CLK                 RCC_AHBPeriph_GPIOB
#define SPIx_CS_SOURCE                   GPIO_PinSource12

//SPI OUTPUTs
#define SPIy                             SPI3
#define SPIy_CLK                         RCC_APB1Periph_SPI3
#define SPIy_IRQn                        SPI3_IRQn

#define SPIy_SCK_PIN                     GPIO_Pin_10
#define SPIy_SCK_GPIO_PORT               GPIOC
#define SPIy_SCK_GPIO_CLK                RCC_AHBPeriph_GPIOC
#define SPIy_SCK_SOURCE                  GPIO_PinSource10
#define SPIy_SCK_AF                      GPIO_AF_6

#define SPIy_MISO_PIN                    GPIO_Pin_11
#define SPIy_MISO_GPIO_PORT              GPIOC
#define SPIy_MISO_GPIO_CLK               RCC_AHBPeriph_GPIOC
#define SPIy_MISO_SOURCE                 GPIO_PinSource11
#define SPIy_MISO_AF                     GPIO_AF_6

#define SPIy_MOSI_PIN                    GPIO_Pin_12
#define SPIy_MOSI_GPIO_PORT              GPIOC
#define SPIy_MOSI_GPIO_CLK               RCC_AHBPeriph_GPIOC
#define SPIy_MOSI_SOURCE                 GPIO_PinSource12
#define SPIy_MOSI_AF                     GPIO_AF_6

#define SPIy_CS_PIN                     GPIO_Pin_11
#define SPIy_CS_GPIO_PORT               GPIOE
#define SPIy_CS_GPIO_CLK                RCC_AHBPeriph_GPIOE
#define SPIy_CS_SOURCE                  GPIO_PinSource11

#include "FreeRTOS.h"
#include "semphr.h"

xSemaphoreHandle xSemaphore;

#endif
