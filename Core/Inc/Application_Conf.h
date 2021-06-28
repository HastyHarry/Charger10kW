
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APPLICATION_CONF_H
#define __APPLICATION_CONF_H

#define PI		 		 				3.14
#define SQRT_2           				1.41421                                                        /*!< Square Root of number 2 */
#define SQRT_3           				1.73205                                                        /*!< Square Root of number 3 */

#define BUCK_Tim1                       htim1
#define BUCK_Tim2                       htim2
#define BUCK_Tim3                       htim3
#define BUCK_Tim4                       htim4
#define BUCK_Tim5                       htim5
#define BUCK_Tim1_OC_CH					TIM_CHANNEL_1
#define BUCK_Tim4_OC_CH					TIM_CHANNEL_4
#define BUCK_Tim5_OC_CH					TIM_CHANNEL_1									/*!<Not in USE>*/

#define BUCK_SW_Frequency				70000											/*!<Switching Freq*/
#define BUCK_Math_Frequency				20000											/*!<Calculations Freq*/
#define BUCK_TO_Timer_Frequency			1000											/*!<TO Freq*/

#define BUCK_Tim1_PWM_CH 				TIM_CHANNEL_3
#define BUCK_Tim4_PWM_CH 				TIM_CHANNEL_2

#define ADC1_CHs						2
#define ADC1_MA_PERIOD_VDC				5
#define ADC1_MA_PERIOD_IDC				5
#define ADC1_MA_PERIOD_RAW				1
#define ADC2_CHs						3
#define ADC2_MA_PERIOD_VDCLINK			5
#define ADC2_MA_PERIOD_IDCLINK			5
#define ADC2_MA_PERIOD_VDCRECT			5
#define ADC2_MA_PERIOD_RAW				1
#define BUCK_ADC1 						hadc1
#define ADC_VAL_CHANGE_SPD_K			0.5

//Rectifier defaults
#define BUCK_IDC_LIM					25
#define BUCK_VAC_REF					400
#define BUCK_VDC_REF					275
#define BUCK_VDC_OV						430
#define BUCK_VDC_HIST					5												/*!< value in %*/
#define BUCK_VDC_REF_LOW_REF			BUCK_VDC_REF-(BUCK_VDC_REF*BUCK_VDC_HIST/100)
#define BUCK_VDC_REF_HIGH_REF			BUCK_VDC_REF+(BUCK_VDC_REF*BUCK_VDC_HIST/100)


#define V_LIM_PID_K_P					0.5//1
#define V_LIM_PID_K_I					0.02//0.05
#define V_LIM_PID_K_D					0.5//0.5
#define V_LIM_PID_W_F					2*PI*BUCK_Math_Frequency/10
#define V_LIM_PID_SAT_UP_PERCENT		100												/*!Value in % of Duty*/
#define V_LIM_PID_SAT_DOWN_PERCENT		-100											/*!Value in % of Duty*/
#define V_LIM_PID_SAT_UP				(V_LIM_PID_SAT_UP_PERCENT/100)*BUCK_VAC_REF
#define V_LIM_PID_SAT_DOWN				(V_LIM_PID_SAT_DOWN_PERCENT/100)*BUCK_VAC_REF
#define V_LIM_PID_HIST					0.0												/*!<Value in %>*/
#define V_LIM_PID_BASE_VAL				0.0*BUCK_VAC_REF
#define V_LIM_PID_ANTIWINDUP			0.0

#define I_LIM_PID_K_P					10.0
#define I_LIM_PID_K_I					0.5
#define I_LIM_PID_K_D					0.0
#define I_LIM_PID_W_F					2*PI*BUCK_Math_Frequency/10
#define I_LIM_PID_SAT_UP_PERCENT		1												/*!Value in % of Duty*/
#define I_LIM_PID_SAT_DOWN_PERCENT		-100											/*!Value in % of Duty*/
#define I_LIM_PID_SAT_UP				(I_LIM_PID_SAT_UP_PERCENT/100)*BUCK_VAC_REF
#define I_LIM_PID_SAT_DOWN				(I_LIM_PID_SAT_DOWN_PERCENT/100)*BUCK_VAC_REF
#define I_LIM_PID_HIST					0.0												/*!<Value in %>*/
#define I_LIM_PID_BASE_VAL				1.0*BUCK_VAC_REF
#define I_LIM_PID_ANTIWINDUP			0.0

#define STUP_PID_K_P					0.0
#define STUP_PID_K_I					0.001
#define STUP_PID_K_D					0.0
#define STUP_PID_W_F					2*PI*BUCK_Math_Frequency/10
#define STUP_PID_SAT_UP_PERCENT			100												/*!Value in % of Duty*/
#define STUP_PID_SAT_DOWN_PERCENT		10												/*!Value in % of Duty*/
#define STUP_PID_SAT_UP					(STUP_PID_SAT_UP_PERCENT/100)*BUCK_VAC_REF
#define STUP_PID_SAT_DOWN				(STUP_PID_SAT_DOWN_PERCENT/100)*BUCK_VAC_REF
#define STUP_PID_HIST					0.0												/*!<Value in %>*/
#define STUP_PID_BASE_VAL				0.0
#define STUP_PID_ANTIWINDUP				0.0


//ADC Settings
#define G_VAC                           4.25//4.708                                     /*!< Gain terms of the AC voltage sensing */
#define B_VAC                           1975                                            /*!< Bias terms of the AC voltage sensing */
#define G_IAC                           10//42.67                                     /*!< Gain terms of the AC current sensing */
#define B_IAC                           1290                                            /*!< Bias terms of the AC current sensing */
#define G_VDC                           0.16//200v devider - .058                      /*!< Gain terms of the DC voltage sensing */
#define B_VDC                           0                                               /*!< Bias terms of the DC voltage sensing */
#define G_IDC                           0.028                                          /*!< Gain terms of the DC current sensing */
#define B_IDC                           0                                           /*!< Bias terms of the DC current sensing */

#define G_VDCLINK                       1                                          /*!< Gain terms of the DC current sensing */
#define B_VDCLINK                       1                                          /*!< Bias terms of the DC current sensing */
#define G_IDCLINK                       1                                          /*!< Gain terms of the DC current sensing */
#define B_IDCLINK                       1                                          /*!< Bias terms of the DC current sensing */
#define G_VRECT                         1                                          /*!< Gain terms of the DC current sensing */
#define B_VRECT                         1                                          /*!< Bias terms of the DC current sensing */

//UART Settings
#define UART_PACKAGE_SIZE				20

#endif //__BUCK_APPLICATION_CONF_H
