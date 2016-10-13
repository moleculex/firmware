#include "platform_config.h"
#include "input.h"
#include "led.h"

void input_digitalInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(X0_RCC | X1_RCC | X2_RCC | X3_RCC | X4_RCC | X5_RCC | X6_RCC | X7_RCC |
						  X8_RCC | X9_RCC | X10_RCC | X11_RCC | X12_RCC | X13_RCC | X14_RCC | X15_RCC |
						  X16_RCC | X17_RCC | X18_RCC | X19_RCC | X20_RCC | X21_RCC | X22_RCC | X23_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = X0_PIN;
	GPIO_Init(X0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X1_PIN;
	GPIO_Init(X1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X2_PIN;
	GPIO_Init(X2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X3_PIN;
	GPIO_Init(X3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X4_PIN;
	GPIO_Init(X4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X5_PIN;
	GPIO_Init(X5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X6_PIN;
	GPIO_Init(X6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X7_PIN;
	GPIO_Init(X7_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X8_PIN;
	GPIO_Init(X8_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X9_PIN;
	GPIO_Init(X9_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X10_PIN;
	GPIO_Init(X10_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X11_PIN;
	GPIO_Init(X11_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X12_PIN;
	GPIO_Init(X12_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X13_PIN;
	GPIO_Init(X13_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X14_PIN;
	GPIO_Init(X14_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X15_PIN;
	GPIO_Init(X15_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X16_PIN;
	GPIO_Init(X16_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X17_PIN;
	GPIO_Init(X17_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X18_PIN;
	GPIO_Init(X18_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X19_PIN;
	GPIO_Init(X19_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X20_PIN;
	GPIO_Init(X20_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X21_PIN;
	GPIO_Init(X21_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X22_PIN;
	GPIO_Init(X22_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = X23_PIN;
	GPIO_Init(X23_PORT, &GPIO_InitStructure);

//DA
	RCC_AHBPeriphClockCmd(D_A_SEL0_RCC | D_A_SEL1_RCC | D_A_SEL2_RCC | D_A_SEL3_RCC | D_A_SEL4_RCC | D_A_SEL5_RCC | D_A_SEL6_RCC | D_A_SEL7_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = D_A_SEL0_PIN;
	GPIO_Init(D_A_SEL0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL1_PIN;
	GPIO_Init(D_A_SEL1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL2_PIN;
	GPIO_Init(D_A_SEL2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL3_PIN;
	GPIO_Init(D_A_SEL3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL4_PIN;
	GPIO_Init(D_A_SEL4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL5_PIN;
	GPIO_Init(D_A_SEL5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL6_PIN;
	GPIO_Init(D_A_SEL6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = D_A_SEL7_PIN;
	GPIO_Init(D_A_SEL7_PORT, &GPIO_InitStructure);

	GPIO_WriteBit(D_A_SEL0_PORT, D_A_SEL0_PIN, 0);
	GPIO_WriteBit(D_A_SEL1_PORT, D_A_SEL1_PIN, 0);
	GPIO_WriteBit(D_A_SEL2_PORT, D_A_SEL2_PIN, 0);
	GPIO_WriteBit(D_A_SEL3_PORT, D_A_SEL3_PIN, 0);
	GPIO_WriteBit(D_A_SEL4_PORT, D_A_SEL4_PIN, 0);
	GPIO_WriteBit(D_A_SEL5_PORT, D_A_SEL5_PIN, 0);
	GPIO_WriteBit(D_A_SEL6_PORT, D_A_SEL6_PIN, 0);
	GPIO_WriteBit(D_A_SEL7_PORT, D_A_SEL7_PIN, 0);

//CV
	RCC_AHBPeriphClockCmd(C_V_SEL0_RCC | C_V_SEL1_RCC | C_V_SEL2_RCC | C_V_SEL3_RCC | C_V_SEL4_RCC | C_V_SEL5_RCC | C_V_SEL6_RCC | C_V_SEL7_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = C_V_SEL0_PIN;
	GPIO_Init(C_V_SEL0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL1_PIN;
	GPIO_Init(C_V_SEL1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL2_PIN;
	GPIO_Init(C_V_SEL2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL3_PIN;
	GPIO_Init(C_V_SEL3_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL4_PIN;
	GPIO_Init(C_V_SEL4_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL5_PIN;
	GPIO_Init(C_V_SEL5_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL6_PIN;
	GPIO_Init(C_V_SEL6_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = C_V_SEL7_PIN;
	GPIO_Init(C_V_SEL7_PORT, &GPIO_InitStructure);

	GPIO_WriteBit(C_V_SEL0_PORT, C_V_SEL0_PIN, 0);
	GPIO_WriteBit(C_V_SEL1_PORT, C_V_SEL1_PIN, 0);
	GPIO_WriteBit(C_V_SEL2_PORT, C_V_SEL2_PIN, 0);
	GPIO_WriteBit(C_V_SEL3_PORT, C_V_SEL3_PIN, 0);
	GPIO_WriteBit(C_V_SEL4_PORT, C_V_SEL4_PIN, 0);
	GPIO_WriteBit(C_V_SEL5_PORT, C_V_SEL5_PIN, 0);
	GPIO_WriteBit(C_V_SEL6_PORT, C_V_SEL6_PIN, 0);
	GPIO_WriteBit(C_V_SEL7_PORT, C_V_SEL7_PIN, 0);
}

int16_t input_digitalRead(int8_t line)
{
	int16_t retval = 0;

	switch(line)
	{
		case 0:
			retval = GPIO_ReadInputDataBit(X0_PORT, X0_PIN);
			led_input(0, (int8_t)retval);
			break;

		case 1:
			retval = GPIO_ReadInputDataBit(X1_PORT, X1_PIN);
			led_input(1, (int8_t)retval);
			break;

		case 2:
			retval = GPIO_ReadInputDataBit(X2_PORT, X2_PIN);
			led_input(2, (int8_t)retval);
			break;

		case 3:
			retval = GPIO_ReadInputDataBit(X3_PORT, X3_PIN);
			led_input(3, (int8_t)retval);
			break;

		case 4:
			retval = GPIO_ReadInputDataBit(X4_PORT, X4_PIN);
			led_input(4, (int8_t)retval);
			break;

		case 5:
			retval = GPIO_ReadInputDataBit(X5_PORT, X5_PIN);
			led_input(5, (int8_t)retval);
			break;

		case 6:
			retval = GPIO_ReadInputDataBit(X6_PORT, X6_PIN);
			led_input(6, (int8_t)retval);
			break;

		case 7:
			retval = GPIO_ReadInputDataBit(X7_PORT, X7_PIN);
			led_input(7, (int8_t)retval);
			break;

		case 8:
			retval = GPIO_ReadInputDataBit(X8_PORT, X8_PIN);
			led_input(8, (int8_t)retval);
			break;

		case 9:
			retval = GPIO_ReadInputDataBit(X9_PORT, X9_PIN);
			led_input(9, (int8_t)retval);
			break;

		case 10:
			retval = GPIO_ReadInputDataBit(X10_PORT, X10_PIN);
			led_input(10, (int8_t)retval);
			break;

		case 11:
			retval = GPIO_ReadInputDataBit(X11_PORT, X11_PIN);
			led_input(11, (int8_t)retval);
			break;

		case 12:
			retval = GPIO_ReadInputDataBit(X12_PORT, X12_PIN);
			led_input(12, (int8_t)retval);
			break;

		case 13:
			retval = GPIO_ReadInputDataBit(X13_PORT, X13_PIN);
			led_input(13, (int8_t)retval);
			break;

		case 14:
			retval = GPIO_ReadInputDataBit(X14_PORT, X14_PIN);
			led_input(14, (int8_t)retval);
			break;

		case 15:
			retval = GPIO_ReadInputDataBit(X15_PORT, X15_PIN);
			led_input(15, (int8_t)retval);
			break;

		case 16:
			retval = GPIO_ReadInputDataBit(X16_PORT, X16_PIN);
			led_input(16, (int8_t)retval);
			break;

		case 17:
			retval = GPIO_ReadInputDataBit(X17_PORT, X17_PIN);
			led_input(17, (int8_t)retval);
			break;

		case 18:
			retval = GPIO_ReadInputDataBit(X18_PORT, X18_PIN);
			led_input(18, (int8_t)retval);
			break;

		case 19:
			retval = GPIO_ReadInputDataBit(X19_PORT, X19_PIN);
			led_input(19, (int8_t)retval);
			break;

		case 20:
			retval = GPIO_ReadInputDataBit(X20_PORT, X20_PIN);
			led_input(20, (int8_t)retval);
			break;

		case 21:
			retval = GPIO_ReadInputDataBit(X21_PORT, X21_PIN);
			led_input(21, (int8_t)retval);
			break;

		case 22:
			retval = GPIO_ReadInputDataBit(X22_PORT, X22_PIN);
			led_input(22, (int8_t)retval);
			break;

		case 23:
			retval = GPIO_ReadInputDataBit(X23_PORT, X23_PIN);
			led_input(23, (int8_t)retval);
			break;
	}

	return retval;
}
