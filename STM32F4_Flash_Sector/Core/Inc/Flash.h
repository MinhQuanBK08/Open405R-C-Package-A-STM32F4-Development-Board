/*
 * Flash.h
 *
 *  Created on: Nov 7, 2022
 *      Author: Minh-Quan Pham
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0    ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1    ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2    ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3    ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4    ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5    ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6    ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7    ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8    ((uint32_t)0x08080000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9    ((uint32_t)0x080A0000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10   ((uint32_t)0x080C0000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11   ((uint32_t)0x080E0000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_12   ((uint32_t)0x08100000) /* Base @ of Sector 7, 128 Kbytes */

#define FLASH_USER_START_ADDR	0x08040000
#define FLASH_USER_END_ADDR		0x08100000

/* Typedefs ------------------------------------------------------------------*/
//1. data size
typedef enum {
	DATA_TYPE_8 = 0, DATA_TYPE_16, DATA_TYPE_32,
} DataTypeDef;

/* Exported functions prototypes ---------------------------------------------*/
//1. Set FLASH Parameters
void FLASH_SetParams(void);
//2. Get Sector form input Address
uint32_t FLASH_GetSector(uint32_t Address);
//3. Erase Sector
void FLASH_EraseSector(uint32_t Address);
//4. Write Flash
uint32_t FLASH_Write(uint32_t idx, void *wrBuf, uint32_t Nsize,
		DataTypeDef dataType);
uint32_t FLASH_Write_Data(uint32_t address, uint32_t *data,
		uint16_t Nsize);
//5. Read Flash
void FLASH_Read(uint32_t idx, void *rdBuf, uint32_t Nsize, DataTypeDef dataType);
void Flash_Read_Data(uint32_t address, uint32_t *data, uint16_t Nsize);

void Convert_To_Str(uint32_t *Data, char *Buf);

void FLASH_Write_NUM(uint32_t address, float Num);
float FLASH_Read_NUM(uint32_t address);

#endif /* INC_FLASH_H_ */
