/*
 * Flash.h
 *
 *  Created on: Nov 7, 2022
 *      Author: Minh-Quan Pham
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "stm32f4xx_hal.h"

uint32_t GetSector(uint32_t Address);

uint32_t Flash_Write_Data(uint32_t StartSectorAddress, uint32_t *data,
    uint16_t numberofwords);
void Flash_Read_Data(uint32_t StartSectorAddress, uint32_t *data,
    uint16_t numberofwords);
void Convert_To_Str(uint32_t *Data, char *Buf);

void Flash_Write_NUM(uint32_t StartSectorAddress, float Num);
float Flash_Read_NUM(uint32_t StartSectorAddress);

#endif /* INC_FLASH_H_ */