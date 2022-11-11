/*
 * Flash.h
 *
 *  Created on: Nov 11, 2022
 *      Author: MinhQuan
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "stm32f4xx_hal.h"

//Typedefs
//1. data size
typedef enum
{
	DATA_TYPE_8=0,
	DATA_TYPE_16,
	DATA_TYPE_32,
}DataTypeDef;

//functions prototypes
//1. Erase Sector
void FLASH_EraseSector(void);

//2. Set Sector Adress
void FLASH_SetSectorAddrs(uint8_t sector, uint32_t addrs);
//3. Write Flash
void FLASH_Write(uint32_t idx, void *wrBuf, uint32_t Nsize, DataTypeDef dataType);
//4. Read Flash
void FLASH_Read(uint32_t idx, void *rdBuf, uint32_t Nsize, DataTypeDef dataType);

#endif /* INC_FLASH_H_ */
