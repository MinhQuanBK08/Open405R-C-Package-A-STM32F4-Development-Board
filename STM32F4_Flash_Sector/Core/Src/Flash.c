/*
 * Flash.c
 *
 *  Created on: Nov 11, 2022
 *      Author: MinhQuan
 */
#include <string.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>
#include "Flash.h"
#include "main.h"

//Private variables
//1. sector start address
static uint32_t FLASH_FirstSector;
static uint32_t FLASH_SectorAddrs;
static uint8_t FLASH_SectorNum;
static uint8_t FLASH_NumOfSectors;

/* External functions --------------------------------------------------------*/
//1. Set FLASH Parameters
void FLASH_SetParams(void) {
	FLASH_FirstSector = FLASH_GetSector(FLASH_USER_START_ADDR);
	FLASH_NumOfSectors = FLASH_GetSector(FLASH_USER_END_ADDR)
			- FLASH_FirstSector + 1;
}
/**
 * @brief Gets the sector of a given address
 * @param None
 * @retval The sector of a given address
 */
uint32_t FLASH_GetSector(uint32_t Address) {
	uint32_t sector = 0;

	if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0)) {
		sector = FLASH_SECTOR_0;
	} else if ((Address < ADDR_FLASH_SECTOR_2)
			&& (Address >= ADDR_FLASH_SECTOR_1)) {
		sector = FLASH_SECTOR_1;
	} else if ((Address < ADDR_FLASH_SECTOR_3)
			&& (Address >= ADDR_FLASH_SECTOR_2)) {
		sector = FLASH_SECTOR_2;
	} else if ((Address < ADDR_FLASH_SECTOR_4)
			&& (Address >= ADDR_FLASH_SECTOR_3)) {
		sector = FLASH_SECTOR_3;
	} else if ((Address < ADDR_FLASH_SECTOR_5)
			&& (Address >= ADDR_FLASH_SECTOR_4)) {
		sector = FLASH_SECTOR_4;
	} else if ((Address < ADDR_FLASH_SECTOR_6)
			&& (Address >= ADDR_FLASH_SECTOR_5)) {
		sector = FLASH_SECTOR_5;
	} else if ((Address < ADDR_FLASH_SECTOR_7)
			&& (Address >= ADDR_FLASH_SECTOR_6)) {
		sector = FLASH_SECTOR_6;
	} else if ((Address < ADDR_FLASH_SECTOR_8)
			&& (Address >= ADDR_FLASH_SECTOR_7)) {
		sector = FLASH_SECTOR_7;
	} else if ((Address < ADDR_FLASH_SECTOR_9)
			&& (Address >= ADDR_FLASH_SECTOR_8)) {
		sector = FLASH_SECTOR_8;
	} else if ((Address < ADDR_FLASH_SECTOR_10)
			&& (Address >= ADDR_FLASH_SECTOR_9)) {
		sector = FLASH_SECTOR_9;
	} else if ((Address < ADDR_FLASH_SECTOR_11)
			&& (Address >= ADDR_FLASH_SECTOR_10)) {
		sector = FLASH_SECTOR_10;
	} else if ((Address < ADDR_FLASH_SECTOR_12)
			&& (Address >= ADDR_FLASH_SECTOR_11)) {
		sector = FLASH_SECTOR_11;
	}
	return sector;
}

//3. Erase Sector
void FLASH_EraseSector(uint32_t Address) {
//	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
//	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
//	EraseInitStruct.Sector = FLASH_FirstSector;
//	EraseInitStruct.NbSectors = FLASH_NumOfSectors;
//	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK) {
//		/* Check the Error Flag with 'HAL_FLASH_GetError()'*/
//		/* FLASH_ErrorTypeDef errorcode = HAL_FLASH_GetError(); */
//		Error_Handler();
//	}
//	/* Note: N???u thao t??c x??a trong b??? nh??? Flash c??ng li??n quan ?????n d??? li???u trong the data ho???c b??? nh??? ?????m,b???n ph???i ch???c ch???n c??c d??? li???u n??y ???????c truy c???p l???i trong khi ch???y code
//	 N???u ??i???u n??y kh??ng th???c hi???n m???t c??ch an to??n c?? th??? x??a b??? nh??? ?????m b???ng c??ch c??i ?????t c??c bit
//	 DCRST v?? ICRST trong thanh ghi FLASH_CR . */
//	__HAL_FLASH_DATA_CACHE_DISABLE();
//	__HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
//
//	__HAL_FLASH_DATA_CACHE_RESET();
//	__HAL_FLASH_INSTRUCTION_CACHE_RESET();
//
//	__HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
//	__HAL_FLASH_DATA_CACHE_ENABLE();
	HAL_FLASH_Unlock();
	FLASH_SectorNum = FLASH_GetSector(Address);
	//Erase the required Flash sector
	FLASH_Erase_Sector(FLASH_SectorNum, FLASH_VOLTAGE_RANGE_3);
	HAL_FLASH_Lock();
}

//4. Write Flash
uint32_t FLASH_Write(uint32_t idx, void *wrBuf, uint32_t Nsize,
		DataTypeDef dataType) {
	uint32_t flashAddress = FLASH_SectorAddrs + idx;
	uint32_t data_Size = 0;

	//Erase sector before write
	FLASH_EraseSector(flashAddress);

	//Unlock Flash
	HAL_FLASH_Unlock();
	//Write to Flash
	switch (dataType) {
	case DATA_TYPE_8:
		for (uint32_t i = 0; i < Nsize; i++) {
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, flashAddress,
					((uint8_t*) wrBuf)[i]);
			data_Size++;
			flashAddress++;
		}
		break;

	case DATA_TYPE_16:
		for (uint32_t i = 0; i < Nsize; i++) {
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, flashAddress,
					((uint16_t*) wrBuf)[i]);
			data_Size++;
			flashAddress += 2;
		}
		break;

	case DATA_TYPE_32:
		for (uint32_t i = 0; i < Nsize; i++) {
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flashAddress,
					((uint32_t*) wrBuf)[i]);
			data_Size++;
			flashAddress += 4;
		}
		break;
	}
	//Lock the Flash space
	HAL_FLASH_Lock();
	return data_Size;
}

//5. Read Flash
void FLASH_Read(uint32_t idx, void *rdBuf, uint32_t Nsize, DataTypeDef dataType) {
	uint32_t flashAddress = FLASH_SectorAddrs + idx;

	switch (dataType) {
	case DATA_TYPE_8:
		for (uint32_t i = 0; i < Nsize; i++) {
			*((uint8_t*) rdBuf + i) = *(uint8_t*) flashAddress;
			flashAddress++;
		}
		break;

	case DATA_TYPE_16:
		for (uint32_t i = 0; i < Nsize; i++) {
			*((uint16_t*) rdBuf + i) = *(uint16_t*) flashAddress;
			flashAddress += 2;
		}
		break;

	case DATA_TYPE_32:
		for (uint32_t i = 0; i < Nsize; i++) {
			*((uint32_t*) rdBuf + i) = *(uint32_t*) flashAddress;
			flashAddress += 4;
		}
		break;
	}
}
