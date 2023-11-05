/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.2                      */
/*     Description: DIO.c	        	 */
/*****************************************/

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"


static void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	if(status==OUTPUT)
	{
		if(pin<PINB0)
		{
			SET_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
		}
		else if(pin<PINC0)
		{
			SET_BIT(DDRB,(pin-PINB0));
			CLR_BIT(PORTB,(pin-PINB0));
		}
		else if(pin<PIND0)
		{
			SET_BIT(DDRC,(pin-PINC0));
			CLR_BIT(PORTC,(pin-PINC0));
		}
		else if(pin<TOTAL_PINS)
		{
			SET_BIT(DDRD,(pin-PIND0));
			CLR_BIT(PORTD,(pin-PIND0));
		}
	}

	else if(status==INPULL)
	{
		if(pin<PINB0)
		{
			CLR_BIT(DDRA,pin);
			SET_BIT(PORTA,pin);
		}
		else if(pin<PINC0)
		{
			CLR_BIT(DDRB,(pin-PINB0));
			SET_BIT(PORTB,(pin-PINB0));
		}
		else if(pin<PIND0)
		{
			CLR_BIT(DDRC,(pin-PINC0));
			SET_BIT(PORTC,(pin-PINC0));
		}
		else if(pin<TOTAL_PINS)
		{
			CLR_BIT(DDRD,(pin-PIND0));
			SET_BIT(PORTD,(pin-PIND0));
		}
	}
	else if(status==INFREE)
	{
		if(pin<PINB0)
		{
			CLR_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
		}
		else if(pin<PINC0)
		{
			CLR_BIT(DDRB,(pin-PINB0));
			CLR_BIT(PORTB,(pin-PINB0));
		}
		else if(pin<PIND0)
		{
			CLR_BIT(DDRC,(pin-PINC0));
			CLR_BIT(PORTC,(pin-PINC0));
		}
		else if(pin<TOTAL_PINS)
		{
			CLR_BIT(DDRD,(pin-PIND0));
			CLR_BIT(PORTD,(pin-PIND0));
		}

	}
}
void DIO_InitPin2(DIO_Port_type port,u8 pin_num,DIO_PinStatus_type status)
{
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		
	}
}
void DIO_WritePin(DIO_Pin_type pin, DIO_PinVoltage_type volt)
{
	if(volt==HIGH)
	{
		if(pin<PINB0)
		{
			SET_BIT(PORTA,pin);
		}
		else if(pin<PINC0)
		{
			SET_BIT(PORTB,(pin-PINB0));
		}
		else if(pin<PIND0)
		{
			SET_BIT(PORTC,(pin-PINC0));
		}
		else if(pin<TOTAL_PINS)
		{
			SET_BIT(PORTD,(pin-PIND0));
		}
	}
	else
	{
		if(pin<PINB0)
		{
			CLR_BIT(PORTA,pin);
		}
		else if(pin<PINC0)
		{
			CLR_BIT(PORTB,(pin-PINB0));
		}
		else if(pin<PIND0)
		{
			CLR_BIT(PORTC,(pin-PINC0));
		}
		else if(pin<TOTAL_PINS)
		{
			CLR_BIT(PORTD,(pin-PIND0));
		}
	}
}


DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_PinVoltage_type volt=LOW;
	if(pin<PINB0)
	{
		volt=READ_BIT(PINA,pin);
	}
	else if(pin<PINC0)
	{
		volt=READ_BIT(PINB,(pin-PINB0));
	}
	else if(pin<PIND0)
	{
		volt=READ_BIT(PINC,(pin-PINC0));
	}
	else if(pin<TOTAL_PINS)
	{
		volt=READ_BIT(PIND,(pin-PIND0));
	}
	return volt;
	
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	if(pin<PINB0)
	{
		TGL_BIT(PORTA,pin);
	}
	else if(pin<PINC0)
	{
		TGL_BIT(PORTB,(pin-PINB0));
	}
	else if(pin<PIND0)
	{
		TGL_BIT(PORTC,(pin-PINC0));
	}
	else if(pin<TOTAL_PINS)
	{
		TGL_BIT(PORTD,(pin-PIND0));
	}
}
void DIO_WritePort(DIO_Port_type port,u8 data)
{
	switch(port)
	{
		case PA:
		PORTA=data;
		break;
		case PB:
		PORTB=data;
		break;
		case PC:
		PORTC=data;
		break;
		case PD:
		PORTD=data;
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 data=0;
	switch(port)
	{
		case PA:
		data=PORTA;
		break;
		case PB:
		data=PORTB;
		break;
		case PC:
		data=PORTC;
		break;
		case PD:
		data=PORTD;
		break;
	}
	return data;
}
void DIO_Init(void)
{
	DIO_Pin_type i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,DIO_PinsStatusArr[i]);
	}
}