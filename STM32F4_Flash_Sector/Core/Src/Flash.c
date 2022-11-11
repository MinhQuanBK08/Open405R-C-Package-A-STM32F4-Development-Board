/*
 * Flash.c
 *
 *  Created on: Nov 11, 2022
 *      Author: MinhQuan
 */

#include "Flash.h"

//Private variables
//1. sector start address
static uint32_t Flash_SectorAddrs;
static uint8_t Flash_SectorNum;

//functions definitions
//1. Erase Sector
void FLASH_EraseSector(void)
{
	HAL_FLASH_Unlock();
	//Erase the required Flash sector
	FLASH_Erase_Sector(Flash_SectorNum, FLASH_VOLTAGE_RANGE_3);
	HAL_FLASH_Lock();
}

//2. Set Sector Adress
void FLASH_SetSectorAddrs(uint8_t sector, uint32_t addrs)
{
	Flash_SectorNum = sector;
	Flash_SectorAddrs = addrs;
}

//3. Write Flash
void FLASH_Write(uint32_t idx, void *wrBuf, uint32_t Nsize, DataTypeDef dataType)
{
	uint32_t flashAddress = Flash_SectorAddrs + idx;

	//Erase sector before write
	FLASH_EraseSector();

	//Unlock Flash
	HAL_FLASH_Unlock();
	//Write to Flash
	switch(dataType)
	{
		case DATA_TYPE_8:
				for(uint32_t i=0; i<Nsize; i++)
				{
					HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, flashAddress , ((uint8_t *)wrBuf)[i]);
					flashAddress++;
				}
			break;

		case DATA_TYPE_16:
				for(uint32_t i=0; i<Nsize; i++)
				{
					HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, flashAddress , ((uint16_t *)wrBuf)[i]);
					flashAddress+=2;
				}
			break;

		case DATA_TYPE_32:
				for(uint32_t i=0; i<Nsize; i++)
				{
					HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flashAddress , ((uint32_t *)wrBuf)[i]);
					flashAddress+=4;
				}
			break;
	}
	//Lock the Flash space
	HAL_FLASH_Lock();
}
//4. Read Flash
void FLASH_Read(uint32_t idx, void *rdBuf, uint32_t Nsize, DataTypeDef dataType)
{
	uint32_t flashAddress = Flash_SectorAddrs + idx;

	switch(dataType)
	{
		case DATA_TYPE_8:
				for(uint32_t i=0; i<Nsize; i++)
				{
					*((uint8_t *)rdBuf + i) = *(uint8_t *)flashAddress;
					flashAddress++;
				}
			break;

		case DATA_TYPE_16:
				for(uint32_t i=0; i<Nsize; i++)
				{
					*((uint16_t *)rdBuf + i) = *(uint16_t *)flashAddress;
					flashAddress+=2;
				}
			break;

		case DATA_TYPE_32:
				for(uint32_t i=0; i<Nsize; i++)
				{
					*((uint32_t *)rdBuf + i) = *(uint32_t *)flashAddress;
					flashAddress+=4;
				}
			break;
	}
}
