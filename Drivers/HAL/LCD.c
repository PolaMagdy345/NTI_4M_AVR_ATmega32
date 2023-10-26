/********************************************************************************/
/*								Author: Paula Magdy								*/
/*								Date:	26/10/2023								*/
/*								Version:	V.1									*/
/*								Description: LCD.c 								*/
/********************************************************************************/


#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Interface.h"
#include "Utils.h"


u8 G_line, G_cell;

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);

	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);

	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0c);		//0x0e ,0x0f
	WriteIns(0x01);		//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}
void LCD_WriteChar(c8 ch)
{
	WriteData(ch);
}
void LCD_WriteString(u8*str)
{
	u8 i,n;
	if(G_cell>=0 && G_cell<=20 && G_line==0)
	{
		n=G_cell;
		for(i=0;str[i] && n<20;n++,i++)
		{
			LCD_WriteChar(str[i]);
		}
		if(n==15)	
		{
			LCD_GoTo(1,0);
			for(;str[i];i++)
			{
				LCD_WriteChar(str[i]);
			}
		}
	}
	else
	{
		for(i=0;str[i];i++)
		{
			LCD_WriteChar(str[i]);
		}

	}
}
void LCD_WriteNumber(s32 num)
{
	c8 str[20];
	u8 i=0;
	if(num<0)
	{
		LCD_WriteChar('-');
		num=-num;
	}
	else if(num==0)
	{
		LCD_WriteChar('0');
		return ;
	}
	while(num)
	{
		str[i]=(s32)((num%10))+'0';
		i++;
		num/=10;
	}
	for(;i>0;i--)
	{
		LCD_WriteChar(str[i-1]);
	}
}
void LCD_GoTo(u8 line,u8 cell)
{
	G_line=line;
	G_cell=cell; 
	if(line==0)
	{
		WriteIns(0x80+cell);
	}
	else if(line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
	else if(line==2)
	{
		WriteIns(0x80+0x14+cell);
	}
	else if(line==3)
	{
		WriteIns(0x80+0x54+cell);
	}
}