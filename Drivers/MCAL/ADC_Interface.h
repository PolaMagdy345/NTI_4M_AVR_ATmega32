/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: DIO_Interface.h    	 */
/*****************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
	}ADC_VoltRef_type;

typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_type;

typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;

typedef enum{
	FREE_RUNNING=0,
	ANALOG_COMPARATOR,
	EXInt_Request,
	TIMER0_COMP_MATCH,
	TIMER0_OVF
	}AutoTrigger_Source_T;

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler);

u16 ADC_Read(ADC_Channel_type CH);

u16 ADC_VoltRead(ADC_Channel_type CH);

u16 ADC_GetRead(void);

void ADC_StartConversion(ADC_Channel_type CH);

u8 ADC_GetReadPeriodic(u16*pdata);

u16 ADC_GetReadNoBlock(void);

void ADCInt_Enable(void);

void ADCInt_Disable(void);

void ADCInt_SetCallBack(void(*LocalPtr)(void));

void ADC_Trig_Source(AutoTrigger_Source_T SELECT);

#endif /* ADC_INTERFACE_H_ */