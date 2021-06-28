/*
******************************************************************************
* @file           : ControlFunc.h
* @brief          : Control and Init functions for Buck Converter
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUCK_CTRL_H
#define __BUCK_CTRL_H

//#include "stdint.h"
//#include "stdio.h"
#include "stm32g4xx_hal.h"
#include "Application_Conf.h"

/* Exported types ------------------------------------------------------------*/
typedef struct {
float Kp;
float Ki;
float Kd;
float SW_Freq;
float Omega;
float Err_pr;
float Up_pr;
float Ui_pr;
float Ud_pr;
float Ui_previous;
float Ud_previous;
float Sat_Up;
float Sat_Down;
float Hist;
float Base_Value;
float Antiwindup_Val;
float Antiwindup_Gain;
uint16_t MA_Step;
FlagStatus Init_Complete;
FlagStatus Antiwindup_Switch;
FlagStatus resetPI;
FlagStatus resetComplete;
}PID_Control_Struct;

typedef struct{
  uint32_t Vdc[ADC1_MA_PERIOD_VDC];
  uint32_t Idc[ADC1_MA_PERIOD_IDC];
  uint32_t Vrect[ADC2_MA_PERIOD_VDCRECT];
  uint32_t Idclink[ADC2_MA_PERIOD_IDCLINK];
  uint32_t Vdclink[ADC2_MA_PERIOD_VDCLINK];
  uint32_t VDC_MA_Counter;
  uint32_t IDC_MA_Counter;
  uint32_t Vrect_MA_Counter;
  uint32_t Idclink_MA_Counter;
  uint32_t Vdclink_MA_Counter;
  float Vdc_MA;
  float Vac_MA;
  float Idc_MA;
  float Vdc_MA_prev;
  float Vac_MA_prev;
  float Idc_MA_prev;

  FlagStatus Ready1;
  FlagStatus Ready2;
}RAW_ADC_Struct;


typedef struct{
  float Vdc;
  float Vac;
  float Idc;
}Cooked_ADC_Struct;

typedef struct {
float G_Vac;
float invG_Vac;
float B_Vac;

float G_Iac;
float invG_Iac;
float B_Iac;

float G_Vdc;
float invG_Vdc;
float B_Vdc;

float G_Idc;
float invG_Idc;
float B_Idc;

float G_Vrect;
float invG_Vrect;
float B_Vrect;

float G_Vdclink;
float invG_Vdclink;
float B_Vdclink;

float G_Idclink;
float invG_Idclink;
float B_Idclink;

FlagStatus ADC_Conf_Complete1;
FlagStatus ADC_Conf_Complete2;
}ADC_Conf_TypeDef;

typedef struct{
	uint32_t PWM_A;
	uint32_t PWM_B;
}BUCK_PWM_Source_Struct;

typedef struct{
	uint32_t OC1;
}BUCK_OC_Source_Struct;


void ADC_Gain_Init(ADC_Conf_TypeDef *BUCK_ADC_Conf,float G_Vac,float B_Vac,float G_Iac,float B_Iac,float G_Vdc,float B_Vdc,float G_Idc,float B_Idc);
void ADC_Gain_Init_2(ADC_Conf_TypeDef *BUCK_ADC_Conf,float G_Vdclink,float B_Vdclink,float G_Idclink,float B_Idclink,float G_Vrect,float B_Vrect);
void PID_Init(PID_Control_Struct* PID_CONFIG, float Kp, float Ki, float Kd, float Freq, float Omega, float Sat_Up, float Sat_Down,
				float Hist, float Antiwindup, float Base_Value);
float PID(float Ref, float Feed, PID_Control_Struct* Conf_struct);
void ADC2Phy_VDC_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values);
void ADC2Phy_IDC_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values);
RAW_ADC_Struct* Read_Volt_DC(void);
void DATA_Processing();
void ADC_MA_VAL_Collection();
void DATA_Acquisition_from_DMA(uint32_t* p_ADC_Data, uint32_t ADC_Type);

#endif //__BUCK_CTRL_H
