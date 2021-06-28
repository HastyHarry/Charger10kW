/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "hrtim.h"
#include "hrtim.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Application_Conf.h"
#include "DPC_Timeout.h"
#include "ControlFunc.h"
#include "PWM_Functions.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
HAL_StatusTypeDef Init_Status;

PID_Control_Struct PID_CONF_StartUp;

PID_Control_Struct UDC_LIMIT_PID;
PID_Control_Struct IDC_LIMIT_PID;

static DMA_PWMDUTY_STRUCT DMA_HRTIM_SRC;
static DMA_UART_STRUCT DMA_UART_SRC;

extern RAW_ADC_Struct Raw_ADC;
extern RAW_ADC_Struct Raw_DMA;

ADC_Conf_TypeDef ADC_Conf;
Cooked_ADC_Struct VDC_ADC_IN_PHY;

uint16_t StartUp;
float PID_Result;
float PID_Result_V;
float PID_Result_I;
float PWM;
uint32_t p_ADC1_Data[ADC1_CHs];
uint32_t p_ADC2_Data[ADC2_CHs];

volatile FlagStatus Calc_Start;
FlagStatus DMA_FLAG;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_HRTIM1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  PID_Init(&PID_CONF_StartUp, STUP_PID_K_P,STUP_PID_K_I,STUP_PID_K_D, BUCK_Math_Frequency, STUP_PID_W_F, STUP_PID_SAT_UP,
		  STUP_PID_SAT_DOWN, STUP_PID_HIST, STUP_PID_ANTIWINDUP, STUP_PID_BASE_VAL);
  PID_Init(&UDC_LIMIT_PID, V_LIM_PID_K_P,V_LIM_PID_K_I,V_LIM_PID_K_D, BUCK_Math_Frequency, V_LIM_PID_W_F, V_LIM_PID_SAT_UP,
		  V_LIM_PID_SAT_DOWN, V_LIM_PID_HIST, V_LIM_PID_ANTIWINDUP, V_LIM_PID_BASE_VAL);
  PID_Init(&IDC_LIMIT_PID, I_LIM_PID_K_P,I_LIM_PID_K_I,I_LIM_PID_K_D, BUCK_Math_Frequency, I_LIM_PID_W_F, I_LIM_PID_SAT_UP,
		  I_LIM_PID_SAT_DOWN, I_LIM_PID_HIST, I_LIM_PID_ANTIWINDUP, I_LIM_PID_BASE_VAL);

  ADC_Gain_Init(&ADC_Conf,G_VAC,B_VAC,G_IAC,B_IAC,G_VDC,B_VDC,G_IDC,B_IDC);

  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);

  DPC_TO_Init();

  DPC_TO_Set(1,1000);

  //HRTIM_PWM_Init(&DMA_HRTIM_SRC);

  HAL_HRTIM_SimpleBaseStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A+HRTIM_TIMERINDEX_TIMER_B+HRTIM_TIMERINDEX_TIMER_C+
		  HRTIM_TIMERINDEX_TIMER_D+HRTIM_TIMERINDEX_TIMER_E);

  HAL_HRTIM_SimpleBaseStart_DMA(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, (uint32_t) &DMA_HRTIM_SRC.chE1, (uint32_t) &(hhrtim1.Instance->sTimerxRegs[4].CMP1xR), 1);
  HAL_HRTIM_WaveformCountStart_IT(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E);
  HAL_HRTIM_UpdateEnable(&hhrtim1,HRTIM_TIMERINDEX_TIMER_E);
  HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TE1);

  HAL_HRTIM_WaveformCountStart_IT(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A);
  HAL_HRTIM_UpdateEnable(&hhrtim1,HRTIM_TIMERINDEX_TIMER_A);
  HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	HAL_ADC_Start_DMA(&hadc1, p_ADC1_Data, ADC1_MA_PERIOD_RAW*ADC1_CHs);
	HAL_ADC_Start_DMA(&hadc2, p_ADC2_Data, ADC2_MA_PERIOD_RAW*ADC2_CHs);

	if (DPC_TO_Check(1)==TO_OUT_TOOK){
		PWM_DUTY_Processing (&DMA_HRTIM_SRC, HRTIM_TIMERID_TIMER_E , 4000);
		PWM_DUTY_Processing (&DMA_HRTIM_SRC, HRTIM_TIMERID_TIMER_A , 4000);
		HAL_GPIO_WritePin(RECT_SW_GPIO_Port, RECT_SW_Pin, GPIO_PIN_SET );
		//HAL_GPIO_TogglePin(GPIOC, LED_VD5_Pin);
		DPC_TO_Set(1,500);
	}

	if(Calc_Start==SET){
		DATA_Processing();
		ADC_MA_VAL_Collection();
		ADC2Phy_VDC_ProcessData(&ADC_Conf,(RAW_ADC_Struct*)Read_Volt_DC(), &VDC_ADC_IN_PHY);
		ADC2Phy_IDC_ProcessData(&ADC_Conf,(RAW_ADC_Struct*)Read_Volt_DC(), &VDC_ADC_IN_PHY);

		if (((float)VDC_ADC_IN_PHY.Vdc) > BUCK_VDC_REF_LOW_REF){
			StartUp=1;
		}
		else if (((float)VDC_ADC_IN_PHY.Vdc) < 20){
			StartUp=0;
			PID_CONF_StartUp.resetPI=SET;
		}

		if (StartUp==0){
			UDC_LIMIT_PID.resetPI = SET;
			IDC_LIMIT_PID.resetPI = SET;
			PID_Result_V = PID(BUCK_VDC_REF, VDC_ADC_IN_PHY.Vdc, &PID_CONF_StartUp);
			PWM = PID_Result_V/BUCK_VAC_REF;
			IDC_LIMIT_PID.resetPI = SET;
			UDC_LIMIT_PID.resetPI = SET;
		}
		else if (StartUp==1){
			PID_Result_V = PID(BUCK_VDC_REF, VDC_ADC_IN_PHY.Vdc, &UDC_LIMIT_PID);
			PID_Result_I = PID(BUCK_IDC_LIM, VDC_ADC_IN_PHY.Idc, &IDC_LIMIT_PID);

			if (PID_Result_V<=PID_Result_I){
				PWM = PID_Result_V/BUCK_VAC_REF;
			}
			else if (PID_Result_V>PID_Result_I){
				PWM = PID_Result_I/BUCK_VAC_REF;
			}
			PID_CONF_StartUp.resetPI = SET;
		}
		//PWM=0.5;
		PWM_DUTY_Processing (&DMA_HRTIM_SRC, HRTIM_TIMERID_TIMER_E , 4000);

		if (VDC_ADC_IN_PHY.Vdc>=BUCK_VDC_OV){
			//HAL_TIMEx_PWMN_Stop_DMA(&BUCK_Tim1, BUCK_Tim1_PWM_CH);
		}
		else if (VDC_ADC_IN_PHY.Vdc <= BUCK_VDC_REF_LOW_REF){
			//HAL_TIMEx_PWMN_Start_DMA(&BUCK_Tim1, BUCK_Tim1_PWM_CH, &BUCK_PWM_SRC.PWM_A, 1);
		}

		Calc_Start = RESET;
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == USART1 ){

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1){
		//20kHz
		Calc_Start = SET;
	}
	else if (htim->Instance == TIM2){
		//20kHz
	}
	if (htim->Instance == TIM3){
		//1kHz
		TimeoutMng();
	}
	else if (htim ->Instance == TIM4){
		//1kHz

	}
}

void HAL_HRTIM_Fault1Callback(HRTIM_HandleTypeDef *hhrtim){
	HAL_GPIO_WritePin(LED_VD5_GPIO_Port, LED_VD5_Pin, GPIO_PIN_SET );
	HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TE1);
}
void HAL_HRTIM_Fault3Callback(HRTIM_HandleTypeDef *hhrtim){
	HAL_GPIO_WritePin(LED_VD4_GPIO_Port, LED_VD4_Pin, GPIO_PIN_SET );
	HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TE1);
}
void HAL_HRTIM_Fault4Callback(HRTIM_HandleTypeDef *hhrtim){
	//HAL_GPIO_WritePin(LED_VD4_GPIO_Port, LED_VD4_Pin, GPIO_PIN_SET );
	//HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TE1);
}

void HAL_HRTIM_Compare1EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx){
	if (TimerIdx == HRTIM_TIMERINDEX_TIMER_E){
		HAL_GPIO_WritePin(LED_VD4_GPIO_Port, LED_VD4_Pin, GPIO_PIN_SET );
	}

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	if (hadc->Instance == ADC1){
		DATA_Acquisition_from_DMA(p_ADC1_Data,1);
	}
	else if (hadc->Instance == ADC2){
		DATA_Acquisition_from_DMA(p_ADC2_Data,2);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
