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
#ifndef __PWM_FUNCTIONS_H
#define __PWM_FUNCTIONS_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

  
void HRTIM_PWM_Init(/*uint32_t  BURST_PWM_Freq_Desidered, uint32_t  PWM_Freq_Desidered,*/  DMA_PWMDUTY_STRUCT *DUTY_SRC);
void PWM_DUTY_Processing (DMA_PWMDUTY_STRUCT *DUTY_SRC, uint32_t Timers, uint32_t Duty);

#endif  //TELEMETRY
