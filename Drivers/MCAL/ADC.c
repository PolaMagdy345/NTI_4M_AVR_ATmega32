/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: ADC.c	        	 */
/*****************************************/

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"

static u8 ADC_BusyFlag;
u8 ADC_Flag;
static void (*ADC_Fptr) (void)=NULLPTR;

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/*vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;	
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	ADCSRA&=0XF8;
	scaler&=0X07;			//128 Prescaller
	ADCSRA|=scaler;
	/*ENABLE ADC*/
	SET_BIT(ADCSRA,ADEN);
	/*prescaler*/	
}


u16 ADC_Read(ADC_Channel_type CH)
{
	u16 adc=0;
	/*set channel mux*/
	ADMUX&=0XE0;
	ADMUX|=CH;
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*w8 ADC finish*/
	while(READ_BIT(ADCSRA,ADSC));
	/*get read*/
	adc=ADCL;
	adc|=(ADCH<<8);
	return adc;
}


void ADC_StartConversion(ADC_Channel_type CH)
{
	if(ADC_BusyFlag==0)
	{
		/*set channel mux*/
		ADMUX&=0XE0;
		ADMUX|=CH;
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_BusyFlag=1;	
	}

}

u16 ADC_GetRead(void)
{
	u16 adc=0;
	/*w8 ADC finish busy wait ( blocking )*/
	while (READ_BIT(ADCSRA,ADSC));
	/*get read*/
	adc=ADCL;
	adc|=(ADCH<<8);
	return adc;
}

u8 ADC_GetReadPeriodic(u16*pdata)
{
	/* periodic check (polling */
	
	if(!READ_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		ADC_BusyFlag=0;
		return 1;
	}
	return 0;
}

u16 ADC_GetReadNoBlock(void)
{
	return ADC;
}
/*return mV*/
u16 ADC_VoltRead(ADC_Channel_type CH)
{
	u16 volt,adc;
	adc=ADC_Read(CH);
	volt=((u32)adc*5000)/1024;
	return volt;	 
}
void ADCInt_Enable(void)
{
	SET_BIT(ADCSRA,ADIE);
}
void ADCInt_Disable(void)
{
	CLR_BIT(ADCSRA,ADIE);
}

void ADCInt_SetCallBack(void(*LocalPtr)(void))
{
	ADC_Fptr=LocalPtr;
}

void ADC_Trig_Source(AutoTrigger_Source_T SELECT)
{
	SET_BIT(ADCSRA,ADATE);
	SFIOR&=0XEF;
	SFIOR|=(SELECT<<5);
}


ISR(ADC_vect)
{
	if(ADC_Fptr!=NULLPTR)
	{
		ADC_Fptr();
	}
}
