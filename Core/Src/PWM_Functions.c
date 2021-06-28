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

//	pTimerCfg.InterruptRequests = HRTIM_MASTER_IT_NONE;
//	pTimerCfg.DMARequests = HRTIM_TIM_DMA_RST;
//	pTimerCfg.DMASize = 0x1;
//	pTimerCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
//	pTimerCfg.InterleavedMode = HRTIM_INTERLEAVED_MODE_DISABLED;
//	pTimerCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
//	pTimerCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
//	pTimerCfg.DACSynchro = HRTIM_DACSYNC_NONE;
//	pTimerCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;
//	pTimerCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
//	pTimerCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
//	pTimerCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
//	pTimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
//	pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
//	pTimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
//	pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
//	pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_D_E_DELAYEDPROTECTION_DISABLED;
//	pTimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
//	pTimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
//	pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
//	pTimerCfg.ReSyncUpdate = HRTIM_TIMERESYNC_UPDATE_UNCONDITIONAL;
//
//	pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chE1;
//	pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[4].CMP1xR);
//
//	if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, &pTimerCfg) != HAL_OK)
//	{
//		Error_Handler();
//	}

	pTimerCfg.InterruptRequests = HRTIM_TIM_IT_CMP1|HRTIM_TIM_IT_CMP4;
	pTimerCfg.DMARequests = HRTIM_TIM_DMA_REP;
	pTimerCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;
	pTimerCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_ENABLED;
	pTimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
	pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_FAULT1|HRTIM_TIMFAULTENABLE_FAULT3
							  |HRTIM_TIMFAULTENABLE_FAULT4;
	pTimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
	pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;
	pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED;
	pTimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
	pTimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
	pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;
	pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
	pTimerCfg.InterruptRequests = HRTIM_MASTER_IT_NONE;
	pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
	pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
	pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;

	pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chE1;
	pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[4].CMP1xR);
	if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, &pTimerCfg) != HAL_OK)
	{
	Error_Handler();
	}
}

void PWM_DUTY_Processing (DMA_PWMDUTY_STRUCT *DUTY_SRC, uint32_t Timers, uint32_t Duty){

	switch (Timers){
		case HRTIM_TIMERID_TIMER_A:
			DUTY_SRC->chA1 = Duty;

		case HRTIM_TIMERID_TIMER_B:
			DUTY_SRC->chB1 = Duty;

		case HRTIM_TIMERID_TIMER_C:
			DUTY_SRC->chC1 = Duty;

		case HRTIM_TIMERID_TIMER_D:
			DUTY_SRC->chD1 = Duty;

		case HRTIM_TIMERID_TIMER_E:
			DUTY_SRC->chE1 = Duty;
	}

}
