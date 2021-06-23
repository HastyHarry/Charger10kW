/**
******************************************************************************
* @file           : DPC_Timeout.c
* @brief          : Timeout Module
******************************************************************************
 *
 * COPYRIGHT(c) 2020 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "DPC_Timeout.h"


/**
* @defgroup Private_Variables                                  Private Variables
  * @{
  */
    TimeoutDataStr_T Timeout_List[6];
/**
*@}
*/


/**
* @defgroup Private_function                                  Private Variables
  * @{
  */
void DPC_TO_Init(void)
{
  for (  uint8_t Temp = 0; Temp < TO_MAX_NUMBER; Temp++){
    Timeout_List[Temp].State = TO_OFF;
    Timeout_List[Temp].Count = 0;  
  }
}
/**
*@}
*/

/**
* @defgroup Private_function                                  Private Variables
  * @{
  */
TO_RET_STATE DPC_TO_Set(uint8_t TO_Num, uint32_t Val)
{
TO_RET_STATE RetState = TO_OUT_ERR;
  
  if(Timeout_List[TO_Num].State == TO_OFF){
    Timeout_List[TO_Num].State = TO_RUN;
    Timeout_List[TO_Num].Count = Val;
    RetState = TO_OUT_OK;
  }
return RetState;
}
/**
*@}
*/

/**
* @defgroup Private_function                                  Private Variables
  * @{
  */
TO_RET_STATE DPC_TO_Check(uint8_t TO_Num)
{
TO_RET_STATE RetState = TO_OUT_ERR;
  if(Timeout_List[TO_Num].State == TO_RUN){
    RetState = TO_OUT_OK;
  }
  else if(Timeout_List[TO_Num].State == TO_TOOK){ 
    RetState = TO_OUT_TOOK;
    Timeout_List[TO_Num].State = TO_OFF;
  }
return RetState; 
}
/**
*@}
*/

/**
* @defgroup Private_function                                  Private Variables
  * @{
  */
void TimeoutMng(void)
{
for (  uint8_t Temp = 0; Temp < TO_MAX_NUMBER; Temp++){
    
  if(Timeout_List[Temp].State == TO_RUN){  
    if(Timeout_List[Temp].Count == 0){
      Timeout_List[Temp].State = TO_TOOK;
    }
    else{
      Timeout_List[Temp].Count--;
    }
  }
 }
}
/**
*@}
*/

/**
* @brief manage the command Load
*/

/**
*@}
*/

/**
* @brief Declare the Rx done flag
*/

/**
* @brief Init the Telemetry package
*/

/**
*@}
*/

/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
