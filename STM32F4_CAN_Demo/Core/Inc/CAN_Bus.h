/*
 * CAN_Bus.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Minh-Quan Pham
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_Bus_H_
#define __CAN_Bus_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported functions prototypes ---------------------------------------------*/
void CAN_Config(CAN_HandleTypeDef* hcan);
void CAN_Receive(CAN_HandleTypeDef* hcan);
void CAN_Transmit(CAN_HandleTypeDef* hcan);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_Bus_H_ */
