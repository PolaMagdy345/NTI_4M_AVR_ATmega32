/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 26/10/2023                  */
/*     Version:	V.1                      */
/*     Description: KeyPad.c	         */
/*****************************************/

#define KEYPAD_PRG	1
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "KeyPad_Interface.h"
#include "KeyPad_Cfg.h"
#define F_CPU 8000000
#include <util/delay.h>

void KEYPAD_Init(void)
{
	u8 r;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}	
}
u8 KEYPAD_Getkey(void)
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS+1;c++)
		{
			if(c==0)
			{
				if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
				{
					key=KeysArr[r][c];
					_delay_ms(10);
					while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
				}
			}
			if(c==1)
			{
				continue;
			}
			else if(c>1)
			{
				if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
				{
					key=KeysArr[r][c-1];
					_delay_ms(10);
					while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
				}
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}
u8 KEYPAD_Binary(void)
{
	u8 key=KEYPAD_Getkey();
	
	if(key=='0' || key=='1' || key=='=' || key=='C')
	{
		return key;
	}
	
	return NO_KEY;
}

