/*
 * CAN_Bus.c
 *
 *  Created on: Sep 20, 2022
 *      Author: Minh-Quan Pham
 */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "CAN_Bus.h"
#include "UART_Bus.h"

/* Private define ------------------------------------------------------------*/
#define CAN_Transmiter_ID 0x055
#define CAN_Receiver_ID 0x0AA

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

uint8_t CAN_TX_Buffer[8]={'H', 'i', ' ', 'C', 'E', '4', '3', '7'};
uint8_t CAN_RX_Buffer[8]={0, 0, 0, 0, 0, 0, 0, 0};
uint8_t crcTable[256];

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 4;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_16TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief CAN2 Initialization Function
  * @param None
  * @retval None
  */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 4;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_16TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
void CRCInit(void) {
  uint8_t _crc;
  for (int i = 0; i < 0x100; i++) {
    _crc = i;

    for (uint8_t bit = 0; bit < 8; bit++) _crc = (_crc & 0x80) ? ((_crc << 1) ^ 0x1D) : (_crc << 1);

    crcTable[i] = _crc;
  }
}

/**
  * @brief CRC Calculation Function
  * @param:
  *        -  data buffer
  *        -  length of data
  * @retval:
  *        -  CRC value (unsigned 8-bit)
  */
uint8_t CalcCRC(uint8_t * buf, uint8_t len) {
        const uint8_t * ptr = buf;
        uint8_t _crc = 0xFF;

        while(len--) _crc = crcTable[_crc ^ *ptr++];

        return ~_crc;
}

/**
  * @brief CAN Filter Configuration Function
  * @param:
  *       - CAN moduel (CAN Handler)
  * @retval None
  */
static void CAN_ConfigFilter(CAN_HandleTypeDef* hcan)
{
  CAN_FilterTypeDef Filter;
  Filter.FilterActivation = CAN_FILTER_ENABLE;
  Filter.FilterIdHigh = CAN_Receiver_ID<<5;
  Filter.FilterMode = CAN_FILTERMODE_IDLIST;
  Filter.FilterScale = CAN_FILTERSCALE_16BIT;
  Filter.FilterBank = 1;
  Filter.FilterFIFOAssignment = CAN_FilterFIFO0;
  Filter.SlaveStartFilterBank =20;
  HAL_CAN_ConfigFilter(hcan, &Filter);

}

/**
  * @brief CAN Configuration Function
  * @param:
  *       - CAN moduel (CAN Handler)
  * @retval None
  */
void CAN_Config(CAN_HandleTypeDef* hcan)
{
  CRCInit();
  CAN_ConfigFilter(hcan);
  HAL_CAN_Start(hcan);
}

void CAN_Receive(CAN_HandleTypeDef* hcan)
{
  HAL_StatusTypeDef Status;
  CAN_RxHeaderTypeDef Can_Header = {0};
  uint32_t FreeLevel;
  //FreeLevel = HAL_CAN_GetRxFifoFillLevel(hcan, CAN_FILTER_FIFO0);
  FreeLevel = HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
  while(FreeLevel > 0)
  {
    Status = HAL_CAN_GetRxMessage(hcan, CAN_FILTER_FIFO0, &Can_Header, CAN_RX_Buffer);
    if(Status != HAL_OK) return;
    for(uint8_t i = 0; i< Can_Header.DLC ;++i)
    {
      printf("%d ", CAN_RX_Buffer[i]);
    }
    printf("\r\n");
    if(Can_Header.StdId == CAN_Receiver_ID)
    {
    }
    FreeLevel = HAL_CAN_GetRxFifoFillLevel(hcan, CAN_FILTER_FIFO0);
  }
}

void CAN_Transmit(CAN_HandleTypeDef* hcan)
{
  CAN_TxHeaderTypeDef Can_Header = {0};
  HAL_StatusTypeDef Status;
  uint32_t Mailbox = 0;
  uint32_t FreeLevel = HAL_CAN_GetTxMailboxesFreeLevel(hcan);
  if(FreeLevel == 0) return;

  Can_Header.DLC = 8;
  Can_Header.StdId = CAN_Transmiter_ID;


  Status = HAL_CAN_AddTxMessage(hcan, &Can_Header, CAN_TX_Buffer, &Mailbox);

  if(Status == HAL_OK)
  {
    printf("Message in mailbox %ld \r\n", Mailbox);
  }
  else
  {
    printf("Transmit Error Status %d Code = 0x%.8lx \r\n", Status, hcan->ErrorCode);
  }
}


