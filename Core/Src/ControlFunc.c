/**
******************************************************************************
* @file           : Buck_Control.c
* @brief          : Control and init functions for Buck Converter
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include <ControlFunc.h>

#include "tim.h"
#include "Application_Conf.h"

/* Private variables ---------------------------------------------------------*/

RAW_ADC_Struct Raw_ADC;
RAW_ADC_Struct Raw_DMA;



/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  PID_Init
  * @param
  * @param
  * @retval None
  */
void PID_Init(PID_Control_Struct* PID_CONFIG, float Kp, float Ki, float Kd, float Freq, float Omega, float Sat_Up, float Sat_Down,
				float Hist, float Antiwindup, float Base_Value ){

	PID_CONFIG->SW_Freq = Freq;
	PID_CONFIG->Omega = Omega;
	PID_CONFIG->Kp = Kp;
	PID_CONFIG->Ki = Ki;
	PID_CONFIG->Kd = Kd;
	PID_CONFIG->Sat_Up = Sat_Up;
	PID_CONFIG->Sat_Down = Sat_Down;
	PID_CONFIG->Hist = Hist;
	PID_CONFIG->Antiwindup_Gain = Antiwindup;
	PID_CONFIG->Base_Value = Base_Value;
	PID_CONFIG->Init_Complete = SET;

}


/**
  * @brief  PID
  * @param  Ref
  * @param  Feed
  * @param  Co nf_struct
  * @retval Result
  */
float PID(float Ref, float Feed, PID_Control_Struct* Conf_struct){

	float Err;
	float Result;
	float Up;
	float Ui;
	float Ud;


	if (Conf_struct->resetPI == SET){
		Conf_struct->Ui_previous = 0;
		Conf_struct->Ud_previous = 0;
		Conf_struct->Err_pr = 0;
		Conf_struct->resetPI = RESET;
	}

	Err = Ref - Feed;

	Up = Conf_struct->Kp * Err;

	if (Err < (Ref*Conf_struct->Hist)/100 && Err>0){
		Ui = (Conf_struct->Ui_previous + Err*Conf_struct->Ki*Conf_struct->Antiwindup_Gain);
	}
	else if (Err > (Ref*Conf_struct->Hist)/100 && Err<0){
		Ui = (Conf_struct->Ui_previous + Err*Conf_struct->Ki*Conf_struct->Antiwindup_Gain);
	}
	else {
		Ui = Conf_struct->Ui_previous + Err*Conf_struct->Ki;
	}

	Ud =(Err - Conf_struct->Err_pr)*Conf_struct->Kd;
	Result = Up+Ui+Ud;

	Result = Conf_struct->Base_Value + Result;

	if (Result>=Conf_struct->Sat_Up){
		Result = Conf_struct->Sat_Up;
	}
	else if (Result<=Conf_struct->Sat_Down){
		Result = Conf_struct->Sat_Down;
	}

	if (Conf_struct->Antiwindup_Switch==SET){
		Conf_struct->Antiwindup_Val = (Conf_struct->Sat_Up - Result)*Conf_struct->Antiwindup_Gain;
	}
	else{
		Conf_struct->Antiwindup_Val=0;
	}

	Conf_struct->Err_pr = Err;
	Conf_struct->Up_pr = Up;
	Conf_struct->Ui_previous = Ui;
	Conf_struct->Ud_previous = Result;

	return Result;
}

/**
  * @brief  ADC_Gain_Init
  * @param  ADC_Conf_TypeDef
  * @retval None
  */

void ADC_Gain_Init(ADC_Conf_TypeDef *BUCK_ADC_Conf,float G_Vac,float B_Vac,float G_Iac,float B_Iac,float G_Vdc,float B_Vdc,float G_Idc,float B_Idc){

	BUCK_ADC_Conf->B_Vac=B_Vac;
	BUCK_ADC_Conf->G_Vac=G_Vac;
	BUCK_ADC_Conf->invG_Vac=(float)(1.0/G_Vac);

	BUCK_ADC_Conf->B_Vdc=B_Vdc;
	BUCK_ADC_Conf->G_Vdc=G_Vdc;
	BUCK_ADC_Conf->invG_Vdc=(float)(1.0/G_Vdc);

	BUCK_ADC_Conf->B_Iac=B_Iac;
	BUCK_ADC_Conf->G_Iac=G_Iac;
	BUCK_ADC_Conf->invG_Iac=(float)(1.0/G_Iac);

	BUCK_ADC_Conf->B_Idc=B_Idc;
	BUCK_ADC_Conf->G_Idc=G_Idc;
	BUCK_ADC_Conf->invG_Idc=(float)(1.0/G_Idc);

	BUCK_ADC_Conf->ADC_Conf_Complete1=SET;
}

/**
  * @brief  ADC_Gain_Init
  * @param  ADC_Conf_TypeDef
  * @retval None
  */

void ADC_Gain_Init_2(ADC_Conf_TypeDef *BUCK_ADC_Conf,float G_Vdclink,float B_Vdclink,float G_Idclink,float B_Idclink,float G_Vrect,float B_Vrect){

	BUCK_ADC_Conf->B_Vdclink = B_Vdclink;
	BUCK_ADC_Conf->G_Vdclink=G_Vdclink;
	BUCK_ADC_Conf->invG_Vdclink=(float)(1.0/G_Vdclink);

	BUCK_ADC_Conf->B_Idclink=B_Idclink;
	BUCK_ADC_Conf->G_Idclink=G_Idclink;
	BUCK_ADC_Conf->invG_Idclink=(float)(1.0/G_Idclink);

	BUCK_ADC_Conf->B_Vrect=B_Vrect;
	BUCK_ADC_Conf->G_Vrect=G_Vrect;
	BUCK_ADC_Conf->invG_Vrect=(float)(1.0/G_Vrect);

	BUCK_ADC_Conf->ADC_Conf_Complete2=SET;
}

/**
  * @brief  ADC2Phy_VDC_ProcessData
  * @param  ADC_Conf
  * @param  p_Data_Sub
  * @param  Cooked_Values
  * @retval Cooked_Values
  */
void ADC2Phy_VDC_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values){

	float B_Vdc=ADC_Conf->B_Vdc;
	float G_Vdc=ADC_Conf->G_Vdc;
	float invG_Vdc=ADC_Conf->invG_Vdc;

	Cooked_Values->Vdc = ((float)((int16_t)p_Data_Sub->Vdc_MA-B_Vdc)*(float)(G_Vdc));

}

/**
  * @brief  ADC2Phy_IDC_ProcessData
  * @param  ADC_Conf
  * @param  p_Data_Sub
  * @param  Cooked_Values
  * @retval Cooked_Values
  */
void ADC2Phy_IDC_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values){

	float B_Idc=ADC_Conf->B_Idc;
	float G_Idc=ADC_Conf->G_Idc;
	float invG_Idc=ADC_Conf->invG_Idc;

	Cooked_Values->Idc = ((float)((int16_t)p_Data_Sub->Idc_MA-B_Idc)*(float)(G_Idc));

}

/**
  * @brief  ADC2Phy_Vrect_ProcessData
  * @param  ADC_Conf
  * @param  p_Data_Sub
  * @param  Cooked_Values
  * @retval Cooked_Values
  */
void ADC2Phy_Vrect_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values){

	float B_Idc=ADC_Conf->B_Vrect;
	float G_Idc=ADC_Conf->G_Vrect;
	float invG_Idc=ADC_Conf->invG_Vrect;

	Cooked_Values->Vrect = ((float)((int16_t)p_Data_Sub->Idc_MA-B_Idc)*(float)(G_Idc));

}

/**
  * @brief  ADC2Phy_Vdclink_ProcessData
  * @param  ADC_Conf
  * @param  p_Data_Sub
  * @param  Cooked_Values
  * @retval Cooked_Values
  */
void ADC2Phy_Vdclink_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values){

	float B_Idc=ADC_Conf->B_Vdclink;
	float G_Idc=ADC_Conf->G_Vdclink;
	float invG_Idc=ADC_Conf->invG_Vdclink;

	Cooked_Values->Vdclink = ((float)((int16_t)p_Data_Sub->Idc_MA-B_Idc)*(float)(G_Idc));

}

/**
  * @brief  ADC2Phy_Idclink_ProcessData
  * @param  ADC_Conf
  * @param  p_Data_Sub
  * @param  Cooked_Values
  * @retval Cooked_Values
  */
void ADC2Phy_Idclink_ProcessData(ADC_Conf_TypeDef *ADC_Conf, RAW_ADC_Struct* p_Data_Sub, Cooked_ADC_Struct* Cooked_Values){

	float B_Idc=ADC_Conf->B_Idclink;
	float G_Idc=ADC_Conf->G_Idclink;
	float invG_Idc=ADC_Conf->invG_Idclink;

	Cooked_Values->Idclink = ((float)((int16_t)p_Data_Sub->Idc_MA-B_Idc)*(float)(G_Idc));

}

/**
  * @brief  Read_Volt_DC
  * @param  None
  * @retval Cooked_ADC_Struct
  */

RAW_ADC_Struct* Read_Volt_DC(void){
  return &Raw_ADC;
}

void DATA_Processing(){
	uint16_t i;
	float Value1 =0;
	float Value2 =0;
	float Value3 =0;

//	MA_Period=10;
//
	if (Raw_DMA.Ready1==SET){
		for (i=0;i<ADC1_MA_PERIOD_RAW;i++){
			//Value1 = Value1 + p_ADC1_Data[i*ADC1_CHs];
			Value2 = Value2 + Raw_DMA.Vdc[i];
			Value3 = Value3 + Raw_DMA.Idc[i];
		}

		Raw_ADC.Vdc[Raw_ADC.VDC_MA_Counter] = Value2/ADC1_MA_PERIOD_RAW;
		Raw_ADC.Idc[Raw_ADC.IDC_MA_Counter] = Value3/ADC1_MA_PERIOD_RAW;
		//Raw_ADC.Vdc[Raw_ADC.MA_Counter] = Raw_DMA.Vdc[0];
		Raw_ADC.VDC_MA_Counter++;
		if (Raw_ADC.VDC_MA_Counter>=ADC1_MA_PERIOD_VDC){
			Raw_ADC.VDC_MA_Counter=0;
		}
		Raw_ADC.IDC_MA_Counter++;
		if (Raw_ADC.IDC_MA_Counter>=ADC1_MA_PERIOD_IDC){
			Raw_ADC.IDC_MA_Counter=0;
		}

		Raw_DMA.Ready1 = RESET;
	}
	else if (Raw_DMA.Ready2==SET){
		for (i=0;i<ADC2_MA_PERIOD_RAW;i++){
			Value1 = Value1 + Raw_DMA.Vrect[i];
			Value2 = Value2 + Raw_DMA.Idclink[i];
			Value3 = Value3 + Raw_DMA.Vdclink[i];
		}

		Raw_DMA.Vrect[Raw_ADC.Vrect_MA_Counter] = Value1/ADC2_MA_PERIOD_RAW;
		Raw_ADC.Idclink[Raw_ADC.Idclink_MA_Counter] = Value2/ADC2_MA_PERIOD_RAW;
		Raw_ADC.Vdclink[Raw_ADC.Vdclink_MA_Counter] = Value3/ADC2_MA_PERIOD_RAW;

		Raw_ADC.Vrect_MA_Counter++;
		if (Raw_ADC.Vrect_MA_Counter>=ADC2_MA_PERIOD_VDCRECT){
			Raw_ADC.Vrect_MA_Counter=0;
		}
		Raw_ADC.Idclink_MA_Counter++;
		if (Raw_ADC.Idclink_MA_Counter>=ADC2_MA_PERIOD_IDCLINK){
			Raw_ADC.Idclink_MA_Counter=0;
		}
		Raw_ADC.Vdclink_MA_Counter++;
		if (Raw_ADC.Vdclink_MA_Counter>=ADC2_MA_PERIOD_VDCLINK){
			Raw_ADC.Vdclink_MA_Counter=0;
		}
		Raw_DMA.Ready2 = RESET;
	}
//	Raw_ADC.Vac[Raw_ADC.MA_Counter] = Value1/ADC1_MA_PERIOD_RAW;
//	if (Raw_DMA.Ready==SET){
//		Value2 = 0;
//		for (i=0;i<ADC1_MA_PERIOD_RAW;i++){
//			//Value1 = Value1 + p_ADC1_Data[i*ADC1_CHs];
//			Raw_ADC.Vdc[i] = Value2 + Raw_DMA.Vdc[i];
//			Raw_ADC.Idc[i] = Value3 + Raw_DMA.Idc[i];
//		}
//		Raw_DMA.Ready = RESET;
//	}

}

void ADC_MA_VAL_Collection(){
	uint16_t i;
	float Value1 =0;
	float Value2 =0;
	float Value3 =0;
	float Value4 =0;
	float Value5 =0;

	for (i=0;i<ADC1_MA_PERIOD_VDC;i++){
		//Value1 = Value1 + Raw_ADC.Vac[i];
		Value2 = Value2 + Raw_ADC.Vdc[i];
		//Value3 = Value3 + Raw_ADC.Idc[i];
	}

	for (i=0;i<ADC1_MA_PERIOD_IDC;i++){
		//Value1 = Value1 + Raw_ADC.Vac[i];
		//Value2 = Value2 + Raw_ADC.Vdc[i];
		Value1 = Value1 + Raw_ADC.Idc[i];
	}

	for (i=0;i<ADC2_MA_PERIOD_IDCLINK;i++){
		Value3 = Value3 + Raw_ADC.Idclink[i];
	}
	for (i=0;i<ADC2_MA_PERIOD_VDCLINK;i++){
		Value4 = Value4 + Raw_ADC.Vdclink[i];
	}
	for (i=0;i<ADC2_MA_PERIOD_VDCRECT;i++){
		Value5 = Value5 + Raw_ADC.Vrect[i];
	}

	//Raw_ADC.Vac_MA = (float)(Value1/(float)(ADC1_MA_PERIOD));
	Raw_ADC.Vdc_MA = (float)(Value2/(float)(ADC1_MA_PERIOD_VDC));
	Raw_ADC.Idc_MA = (float)(Value1/(float)(ADC1_MA_PERIOD_IDC));
	Raw_ADC.Idclink_MA = (float)(Value3/(float)(ADC2_MA_PERIOD_IDCLINK));
	Raw_ADC.Vdclink_MA = (float)(Value4/(float)(ADC2_MA_PERIOD_VDCLINK));
	Raw_ADC.Vrect_MA = (float)(Value5/(float)(ADC2_MA_PERIOD_VDCRECT));
}

void DATA_Acquisition_from_DMA(uint32_t* p_ADC_Data, uint32_t ADC_Type) {

	uint32_t i;

	switch (ADC_Type){
	case 1:
		for (i=0;i<ADC1_MA_PERIOD_RAW;i++){
			//Value1 = Value1 + p_ADC1_Data[i*ADC1_CHs];
			Raw_DMA.Vdc[i] = p_ADC_Data[i*ADC1_CHs+1];
			Raw_DMA.Idc[i] = p_ADC_Data[i*ADC1_CHs];
		}

		Raw_DMA.Ready1 = SET;
	case 2:
		for (i=0;i<ADC2_MA_PERIOD_RAW;i++){
			//Value1 = Value1 + p_ADC1_Data[i*ADC1_CHs];
			Raw_DMA.Vdclink[i] = p_ADC_Data[i*ADC2_CHs];
			Raw_DMA.Vrect[i] = p_ADC_Data[i*ADC2_CHs+1];
			Raw_DMA.Idclink[i] = p_ADC_Data[i*ADC2_CHs+2];
		}
		Raw_DMA.Ready2 = SET;
	}

}


