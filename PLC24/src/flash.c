#include "flash.h"
#include "stm32f30x_flash.h"

void flash_write(char *buffer, int16_t length)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	FLASH_ErasePage((uint32_t)0x08020000);

	for(int16_t n = 0; n < length; n++)
		FLASH_ProgramWord((uint32_t)(0x08020000 + n*4), (uint32_t)buffer[n]);

	FLASH_Lock();
}

void flash_read(char *buffer, int16_t length)
{
	for(int16_t n = 0; n < length; n++)
	{
		buffer[n] = (char)(*(__IO uint32_t *)(0x08020000 + n*4));
	}
}
