/**
******************************************************************************
* @file           : PWM_Functions.c
* @brief          : Functions for PWM control using G334
******************************************************************************


/* Includes ------------------------------------------------------------------*/
#include "PWM_Functions.h"
#include "hrtim.h"

HRTIM_HandleTypeDef hhrtim1;

//void HRTIM_PWM_Init(uint32_t  BURST_PWM_Freq_Desidered,uint32_t  PWM_Freq_Desidered, DPC_PWM_StatusTypeDef DPC_PWM_SET,
//		DPC_PWM_TypeDef *tDPC_PWM_loc, DMA_PWMDUTY_STRUCT *DUTY_SRC){
//
//}

void HRTIM_PWM_Init(/*uint32_t  BURST_PWM_Freq_Desidered, uint32_t  PWM_Freq_Desidered,*/  DMA_PWMDUTY_STRUCT *DUTY_SRC)
{
	HRTIM_TimerCfgTypeDef pTimerCfg = {0};

	//	pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;
	//  pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED;

	pTimerCfg.DMARequests = HRTIM_TIM_DMA_REP;
	pTimerCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;
	pTimerCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
	pTimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
	pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_FAULT1;/*|HRTIM_TIMFAULTENABLE_FAULT3
							  |HRTIM_TIMFAULTENABLE_FAULT4;*/
	pTimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
	pTimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
	pTimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
	pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;
	pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_D_E_DELAYEDPROTECTION_DISABLED;
	pTimerCfg.InterruptRequests = HRTIM_TIM_IT_CMP1|HRTIM_TIM_IT_CMP4|HRTIM_TIM_IT_UPD|HRTIM_TIM_IT_SET1|HRTIM_TIM_IT_REP|
									HRTIM_TIM_IT_CMP2|HRTIM_TIM_IT_CMP3;
	pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
	pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chE1;
	pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[4].CMP1xR);
	pTimerCfg.DMASize = 0x1;
	if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, &pTimerCfg) != HAL_OK)
	{
	Error_Handler();
	}

	pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chD1;
	pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[3].CMP1xR);
	pTimerCfg.DMASize = 0x1;
	if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, &pTimerCfg) != HAL_OK)
	{
	Error_Handler();
	}
}

void PWM_DUTY_Processing (DMA_PWMDUTY_STRUCT *DUTY_SRC, PWM_Timers TIM, float Duty){

	uint32_t Period_Value;
	uint32_t Duty_Value;

	switch (TIM){
		case TIMER_A:
			Period_Value = hhrtim1.Instance->sTimerxRegs[0].PERxR;
			Duty_Value = (uint32_t) (Duty*Period_Value);
			DUTY_SRC->chA1 = Duty_Value;
		break;
		case TIMER_B:
			Period_Value = hhrtim1.Instance->sTimerxRegs[1].PERxR;
			Duty_Value = (uint32_t) (Duty*Period_Value);
			DUTY_SRC->chB1 = Duty_Value;
		break;
		case TIMER_C:
			Period_Value = hhrtim1.Instance->sTimerxRegs[2].PERxR;
			Duty_Value = (uint32_t) (Duty*Period_Value);
			DUTY_SRC->chC1 = Duty_Value;
		break;
		case TIMER_D:
			Period_Value = hhrtim1.Instance->sTimerxRegs[3].PERxR;
			Duty_Value = (uint32_t) (Duty*Period_Value);
			DUTY_SRC->chD1 = Duty_Value;
		break;
		case TIMER_E:
			Period_Value = hhrtim1.Instance->sTimerxRegs[4].PERxR;
			Duty_Value = (uint32_t) (Duty*Period_Value);
			DUTY_SRC->chE1 = Duty_Value;
		break;
	}
}
