/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct
{
	uint32_t chA1;
	uint32_t chA2;
	uint32_t chB1;
	uint32_t chB2;
	uint32_t chC1;
	uint32_t chC2;
	uint32_t chD1;
	uint32_t chD2;
	uint32_t chE1;
	uint32_t chE2;
} DMA_PWMDUTY_STRUCT;

typedef struct
{
	uint8_t Received[30];
	uint8_t Transmit[30];

} DMA_UART_STRUCT;

typedef enum{
	TIMER_A,
	TIMER_B,
	TIMER_C,
	TIMER_D,
	TIMER_E
} PWM_Timers;

typedef enum{
	IDLE,
	Waiting_For_AC,
	Ready_to_Charge,
	Charging,
	Fault_OV_DClink,
	Fault_I_DClink,
	Fault_Res
} System_state;


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUCK_SW_Pin GPIO_PIN_0
#define BUCK_SW_GPIO_Port GPIOB
#define RECT_SW_Pin GPIO_PIN_1
#define RECT_SW_GPIO_Port GPIOB
#define LED_VD5_Pin GPIO_PIN_11
#define LED_VD5_GPIO_Port GPIOC
#define LED_VD4_Pin GPIO_PIN_12
#define LED_VD4_GPIO_Port GPIOC
#define LED_VD10_Pin GPIO_PIN_5
#define LED_VD10_GPIO_Port GPIOB
#define LED_VD11_Pin GPIO_PIN_6
#define LED_VD11_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define LoWord(param) ((unsigned *)&param)[0]
#define HiWord(param) ((unsigned *)&param)[1]

#define Lowest(param) ((uint8_t *)&param)[0]
#define Lo(param) 	  ((uint8_t *)&param)[1]
#define Hi(param) 	  ((uint8_t *)&param)[2]
#define Highest(param)((uint8_t *)&param)[3]

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
