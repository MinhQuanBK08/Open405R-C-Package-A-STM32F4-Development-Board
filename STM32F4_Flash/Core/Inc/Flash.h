/*
 * Flash.h
 *
 *  Created on: Nov 7, 2022
 *      Author: Minh-Quan Pham
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

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

uint32_t GetSector(uint32_t Address);

uint32_t Flash_Write_Data(uint32_t StartSectorAddress, uint32_t *data,
    uint16_t numberofwords);
void Flash_Read_Data(uint32_t StartSectorAddress, uint32_t *data,
    uint16_t numberofwords);
void Convert_To_Str(uint32_t *Data, char *Buf);

void Flash_Write_NUM(uint32_t StartSectorAddress, float Num);
float Flash_Read_NUM(uint32_t StartSectorAddress);

#endif /* INC_FLASH_H_ */
