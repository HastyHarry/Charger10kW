/**
 * @file    Timeout.h
 * @author  Smart Power - SRA CL
 * @version V1.0.0
 * @date    18-Dec-2019
 * @brief   .
 * @details
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
 * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
 *
 * <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics</center></h2>
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMEOUT_H
#define __TIMEOUT_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stddef.h"


/** @defgroup Exported_Tyoedef        Exported Typedef
 * @{
 */

     
typedef enum{
    TO_OFF = 0,
    TO_RUN,    
    TO_TOOK    
  } TO_STATE;   

typedef struct{
  uint32_t Count;
  TO_STATE State;
} TimeoutDataStr_T;


     
typedef enum{
    TO_OUT_ERR = 0,
    TO_OUT_OK,    
    TO_OUT_TOOK    
  } TO_RET_STATE;   

#define TO_MAX_NUMBER      6

#define TO_LED    	   0
#define TO_COM		   1
#define TO_UART        2
#define TO_INDX2       3
#define TO_INDX3       4
#define TO_INDX4       5

#define TEL_TIMEOUT_VAL     200
  
/**
 * @}
 */

/** @defgroup Exported_Functions        Exported Functions
 * @{
 */
void DPC_TO_Init(void);
TO_RET_STATE DPC_TO_Set(uint8_t TO_Num, uint32_t Val);
TO_RET_STATE DPC_TO_Check(uint8_t TO_Num);
void TimeoutMng(void); 
/**
 * @}
 */


#endif  //TELEMETRY

/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
