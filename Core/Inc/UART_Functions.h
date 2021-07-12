/**
 * @file    PWM_Functions.h
 * @author  Antushev N.
 * @version V1.0.0
 * @date    16-Jun-2021
 * @brief   .
 * @details
 *
 *
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_FUNCTIONS_H
#define __UART_FUNCTIONS_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Application_Conf.h"

typedef struct{
	uint8_t Header1;
	uint8_t Header2;
	uint8_t Source;
	uint8_t Command_type;
	uint16_t Addr[5];
	uint16_t Data[5];
	uint8_t DataLength;

}UART_Message_Struct;

UART_Message_Struct UART_MSG;

typedef enum{
	UART_MSG_Types_READ = 01,
	UART_MSG_Types_Write = 02,
	UART_MSG_Types_WriteConfirm = 0x22
}UART_MSG_Types;
  
void UART_Message_Init(UART_Message_Struct *MSG_SRC_Struct, uint16_t Header, uint8_t Source_Addr);
void UART_Message_Send(UART_Message_Struct *MSG_SRC_Struct, uint16_t Addresses[5], uint16_t Data[5], UART_MSG_Types Command, uint8_t HowMuchData);
void UART_Message_Send_Package_Processing(UART_Message_Struct *MSG_SRC_Struct,DMA_UART_STRUCT *UART_Cooked);
void UART_Received_Message_Processing(UART_Message_Struct *MSG_SRC_Struct, DMA_UART_STRUCT *SOURCE );

#endif
