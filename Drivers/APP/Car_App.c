/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 2/11/2023                   */
/*     Version:	V.1                      */
/*     Description: Car_App.h		     */
/*****************************************/

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "Sensors_Interface.h"
#include "EX_Interrupt_Interface.h"
#include "ADC_Interface.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "UART_Interface.h"
#include "UART_Services.h"
#include "SPI.h"
#include "App_Interface.h"

/**** Speed ****/
/*
	0 ->20
	1 ->40
	9 ->100
	F -> Two motors forward
	R -> Left Motor On
	L -> Right Motor On
	S -> Motor Off
*/
/*** Servos ***/
/*
	A	-> Servo1	S1
	B	-> Servo2	S1
	C	-> Servo3	S2
	D	-> Servo4	S3
	T	-> Temp Status
*/
#define Motor1	'R'
#define Motor2	'L'
u8 Timer2_Counter;
u16 SERVO_OFF;/*
void Servo(u8 angle)
{
	if(angle>180)
	{
		angle=180;
	}
	SERVO_OFF=(((u16)angle*8)/180)+2;
}

void Servo_Callback(void)
{
	TCNT2=6;
	Timer2_Counter++;
	if(Timer2_Counter==80)
	{
		DIO_WritePin(PIND7,HIGH);
		Timer2_Counter=0;
	}
	if(Timer2_Counter==SERVO_OFF)
	{
		DIO_WritePin(PIND7,LOW);
	}
}*/
u8 flag;
u8 system=Status;
u8 Motor_F='Z';
void App_Runnable(void)
{
	u8 Msg='Z';
	u8 Slave_Response=0;
	if(flag==0)
	{
		LCD_GoTo(0,0);
		LCD_WriteString("S1:");
		LCD_GoTo(0,14);
		LCD_WriteString("S2:");
		LCD_GoTo(1,0);
		LCD_WriteString("S3:");
		LCD_GoTo(1,14);
		LCD_WriteString("S4:");
		LCD_GoTo(2,0);
		LCD_WriteString("ML:");
		LCD_GoTo(2,14);
		LCD_WriteString("MR:");
		LCD_GoTo(3,5);
		LCD_WriteString("T:");
		flag=1;
	}
	
	Msg=UART_Receive();

	if(Msg==0x0d || Msg==0x0a)
	{
		Msg='Z';
	}

	#if SPI_MODE
	if(system==Master)
	{
		if(Msg=='A' || Msg=='B' || (Msg>='0' && Msg<='9') || Msg=='F'|| Msg=='S'|| Msg=='L'|| Msg=='R')
		{

			if(Msg=='F' || Msg=='S'|| Msg=='L'|| Msg=='R')
			{
				Motor_F=Msg;
			}
			if(Msg>='0' && Msg<='9')
			{
// 				DIO_WritePin(PINC1,LOW);
// 				DIO_WritePin(PINC0,HIGH);
				if(Motor_F=='F')
				{
					LCD_GoTo(2,3);
					LCD_WriteString("   ");
					LCD_GoTo(2,3);
					LCD_WriteNumber(20+((Msg-'0')*20));
					LCD_GoTo(2,17);
					LCD_WriteString("   ");
					LCD_GoTo(2,17);
					LCD_WriteNumber(20+((Msg-'0')*20));
				}
				if(Motor_F=='L')
				{
					LCD_GoTo(2,3);
					LCD_WriteString("   ");
					LCD_GoTo(2,3);
					LCD_WriteNumber(20+((Msg-'0')*20));
				}
				if(Motor_F=='R')
				{
					LCD_GoTo(2,17);
					LCD_WriteString("   ");
					LCD_GoTo(2,17);
					LCD_WriteNumber(20+((Msg-'0')*20));
				}
			}
		}
		else if(Msg=='C' || Msg=='D' || Msg=='T') 
		{
			DIO_WritePin(PINC0,LOW);
			DIO_WritePin(PINC1,HIGH);
		}
				Slave_Response=SPI_SendReceive(Msg);
				_delay_ms(100);

	}
	#else

		Msg=SPI_SendReceive(Domie);
		/*
		if(Msg==Motor1)
		Motor_F=Motor1;
		else if(Msg==Motor2)
		Motor_F=Motor2;
		*/
		if(Msg>='0' && Msg<='9')
		{
			if(Motor_F==Motor1)
			OCR0=20+((Msg-'0')*20);
			else if(Motor_F==Motor2)
			OCR2=20+((Msg-'0')*20);
			else
			{
			OCR0=20+((Msg-'0')*20);
			OCR2=20+((Msg-'0')*20);
			}
		}
		if(Msg=='S')
		{
			if(Motor_F==Motor1)
			OCR0=0;
			else if(Motor_F==Motor2)
			OCR2=0;
			else
			{
				OCR0=0;
				OCR2=0;
			}
		}
	}
	#endif
}