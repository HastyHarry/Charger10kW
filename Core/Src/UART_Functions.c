/**
******************************************************************************
* @file           : PWM_Functions.c
* @brief          : Functions for PWM control using G334
******************************************************************************


/* Includes ------------------------------------------------------------------*/
#include "UART_Functions.h"


void UART_Message_Init(UART_Message_Struct *MSG_SRC_Struct, uint16_t Header, uint8_t Source_Addr){
	MSG_SRC_Struct->Header1 = Lowest(Header);
	MSG_SRC_Struct->Header1 = Lo(Header);
	MSG_SRC_Struct->Source = Source_Addr;
}

void UART_Message_Send(UART_Message_Struct *MSG_SRC_Struct, uint16_t Addresses[5], uint16_t Data[5], UART_MSG_Types Command, uint8_t HowMuchData)
{
	uint8_t i;
	switch (Command){
	case UART_MSG_Types_READ:
		MSG_SRC_Struct->Command_type = UART_MSG_Types_READ;
		MSG_SRC_Struct->DataLength = HowMuchData;
		for(i=0;i<HowMuchData;i++){
			MSG_SRC_Struct->Addr[i]=Addresses[i];
		}
	break;
	case UART_MSG_Types_Write:

	break;
	case UART_MSG_Types_WriteConfirm:

	break;
	}

}

void UART_Message_Send_Package_Processing(UART_Message_Struct *MSG_SRC_Struct,DMA_UART_STRUCT *UART_Cooked){

	UART_Cooked->Transmit[0] = MSG_SRC_Struct->Header1;
	UART_Cooked->Transmit[1] = MSG_SRC_Struct->Header2;
	UART_Cooked->Transmit[2] = MSG_SRC_Struct->Source;
	UART_Cooked->Transmit[3] = MSG_SRC_Struct->Command_type;
	UART_Cooked->Transmit[4] = MSG_SRC_Struct->DataLength;
	UART_Cooked->Transmit[5] = Lowest(MSG_SRC_Struct->Addr[0]);
	UART_Cooked->Transmit[6] = Lo(MSG_SRC_Struct->Addr[0]);
	UART_Cooked->Transmit[7] = Lowest(MSG_SRC_Struct->Data[0]);
	UART_Cooked->Transmit[8] = Lo(MSG_SRC_Struct->Data[0]);
	UART_Cooked->Transmit[9] = Lowest(MSG_SRC_Struct->Addr[1]);
	UART_Cooked->Transmit[10] = Lo(MSG_SRC_Struct->Addr[1]);
	UART_Cooked->Transmit[11] = Lowest(MSG_SRC_Struct->Data[1]);
	UART_Cooked->Transmit[12] = Lo(MSG_SRC_Struct->Data[1]);
	UART_Cooked->Transmit[13] = Lowest(MSG_SRC_Struct->Addr[2]);
	UART_Cooked->Transmit[14] = Lo(MSG_SRC_Struct->Addr[2]);
	UART_Cooked->Transmit[15] = Lowest(MSG_SRC_Struct->Data[2]);
	UART_Cooked->Transmit[16] = Lo(MSG_SRC_Struct->Data[2]);
	UART_Cooked->Transmit[17] = Lowest(MSG_SRC_Struct->Addr[3]);
	UART_Cooked->Transmit[18] = Lo(MSG_SRC_Struct->Addr[3]);
	UART_Cooked->Transmit[19] = Lowest(MSG_SRC_Struct->Data[3]);
	UART_Cooked->Transmit[20] = Lo(MSG_SRC_Struct->Data[3]);
	UART_Cooked->Transmit[21] = Lowest(MSG_SRC_Struct->Addr[4]);
	UART_Cooked->Transmit[22] = Lo(MSG_SRC_Struct->Addr[4]);
	UART_Cooked->Transmit[21] = Lowest(MSG_SRC_Struct->Data[4]);
	UART_Cooked->Transmit[22] = Lo(MSG_SRC_Struct->Data[4]);

}

void UART_Received_Message_Processing(UART_Message_Struct *MSG_SRC_Struct, DMA_UART_STRUCT *SOURCE ){

}
