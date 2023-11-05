/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: Timers_Services.c    */
/*****************************************/

#include "Timers.h"
#include "Timers_Services.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"

static volatile u16 t1,t2,t3,flag=0;

/**********************************************PWM*********************************************************/
/*
void PWM_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8,OCRA_NON_INVERTING,OCRB_DISCONNECTED);
	
}*/

void Servo_ADC_SetPosition(u16 P)		//ADC read for timer1
{
	DutyName=(((u32)P*1000)/1024)+999;
}
void PWM_Freq_KHZ(u16 freq)
{
	if (freq==0);
	else
	{
		u16 Ttotal=1000/freq;
		if (Ttotal>=1)
		{
			ICR1=Ttotal-1;
		}
		else ICR1=0;
		
	}
}
void PWM_Freq_HZ(u16 freq)
{
	if (freq==0);
	else
	{
		u16 Ttotal=(u32)1000000/freq;
		if (Ttotal>=1)
		{
			ICR1=Ttotal-1;
		}
		else ICR1=0;
	}



}
void PWM_Duty(u16 duty)
{
	 if (duty<=100)
	{
		u16 Ton=((u32)duty*(ICR1+1))/100;
		if (Ton>1)
		{
			OCR1A=Ton-1;	
		}
		else
		OCR1A=0;	
	}
}
/******************************************Set Interrupt Time******************************************************/
/** 0 to 65 **/
void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void))
{
	//Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	OCR1A=(time*1000)-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();	
}
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void))
{
	//Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	OCR1A=(time)-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}

/**********************************************Measure PWM*********************************************************/
void PWM_Measure2(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	flag=0;
	TCNT1=0;
	while (DIO_ReadPin(PIND6));
	while (!DIO_ReadPin(PIND6));
	TCNT1=0;
	while (DIO_ReadPin(PIND6));
	Ton=TCNT1;
	TCNT1=0;
	while (!DIO_ReadPin(PIND6));
	Toff=TCNT1;
	*Pduty=((u32)Ton*100)/(Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);
}

static void Func_ICU(void);

void PWM_Measure(u32* Pfreq,u8* Pduty,u32 timeout)
{
	u16 Ton,Toff;
	u32 c=0;
	TCNT1=0;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	flag=0;
	while((flag<3)&&(c<timeout))
	{
		c++;
		_delay_us(1);
	}
   if (flag==3)
   {
	  Ton=t2-t1;//+c*65535
	  Toff=t3-t2;

	  *Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	  *Pfreq=(u32)1000000/((u32)Toff+Ton); 
   }
   else
   {
	   *Pfreq=0;
	   if (DIO_ReadPin(PIND6)==LOW)
	   {
		   *Pduty=0;
	   }
	   else
	   {
		   *Pduty=100;
	   }
   }
}
static void Func_ICU(void)
{
	if (flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag==1)
	{
		t2=ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag=2;
	}
	else if (flag==2)
	{
		t3=ICR1;
		Timer1_ICU_InterruptDisable();
		flag=3;
	}

}/*
static void f1(void)
{
	if (flag==0)
	{
	TCNT1=0;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();

	}
}

static u8 f2(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	
	if (flag==3)
	{
	Ton=t2-t1;
	Toff=t3-t2;

	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);
	flag=0;
	return 1;
	
	}
	return 0;
}*/


static void Timer_func(void);
static u32 NofOverFlow=0;
static void(*fptr_timer)(void);
void Timer1_SetInterruptTime_s (u16 time,void(*LocalFptr)(void))
{
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
	OCR1A=999;
	
	NofOverFlow=time*1000;
	
	fptr_timer=LocalFptr;
	Timer1_OCA_SetCallBack(Timer_func);
	Timer1_OCA_InterruptEnable();
}

static void Timer_func(void)
{
	static u32 c=0;
	c++;
	if (c==NofOverFlow)
	{
		c=0;
		fptr_timer();
	}
}


/*
ISR(TIMER0_OVF_vect)
{
	static u8 flag=0;
	if (flag==0)
	{
		DIO_WritePin(PINC0,HIGH);
		flag=1;
		TCNT0=196;
	}
	else if (flag==1)
	{
		DIO_WritePin(PINC0,LOW);
		flag=0;
		TCNT0=116;
	}
}*/
/*
ISR(TIMER0_OVF_vect)
{
	static u8 c=0;
	c++;
	TCNT0=236;
	if (c==7)
	{
		DIO_WritePin(PINC0,HIGH);
	}
	else if (c==10)
	{
		DIO_WritePin(PINC0,LOW);
		c=0;
	}
}*/


/*
ISR(TIMER0_OVF_vect)
{
	static u16 c=0;
	static u16 c2=0;
	c++;
	c2++;
	if (c==3907)
	{
		DIO_TogglePin(PINC0);
		TCNT0=192;
		c=0;
	}
	if (c2==7812)
	{
		DIO_TogglePin(PINC1);
		c2=0;
	}
	
}*/
/*
ISR(TIMER0_OVF_vect)
{
	static u16 c=0;
	TCNT0=6;
	c++;
	if (c%20==0)
	{
		DIO_TogglePin(PINC0);
	}
	if (c%40==0)
	{
		DIO_TogglePin(PINC1);
	}
	if (c%100==0)
	{
		DIO_TogglePin(PINC2);
	}
	if (c==200)
	{
		c=0;
	}
}
*/


/*
ISR(int_5ms)
{
	static u16 c=0;
	TCNT0=6;
	c++;
	
		DIO_TogglePin(PINC0);
	if (c%2==0)
	{
		DIO_TogglePin(PINC1);
	}
	if (c%5==0)
	{
		DIO_TogglePin(PINC2);
	}
	if (c==10)
	{
		c=0;
	}
}*/

