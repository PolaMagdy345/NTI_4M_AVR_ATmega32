/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: UART.c	     	  	 */
/*****************************************/

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "UART_Interface.h"
#include "UART_Services.h"
#include "LCD_Interface.h"

static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;


void UART_Init()
{
	//baud rate 9600
	
	UBRRL=51;
	//Normal Speed
	
	CLR_BIT(UCSRA,U2X);	
	
	//frame (stop,data,parity)		//1 STOP NO PARITY 8 DATA BITS
	
	//ENABLE TX RX
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));		//while UDRE equals one so you will write data
	UDR=data;
	
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}


u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));  //BLOCKING
	return UDR;
}

u8 UART_ReceivePeriodic(u8* Pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*Pdata=UDR;
		return 1;
	}
	return 0;
}


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}
/*********************************************************/

//extern u8 UART_Queue[QUEUE_SIZE];

void rx_func(void)
{
	if(UART_Circular_inQueue()==QUEUE_FULL)
	{
		LCD_GoTo(1,0);
		LCD_WriteString("Queue Full!   ");
		UART_ReceiveNoBlock();
	}
	
}
/************************2D Sentences Queue******************************/

extern u8 UART_Queue2D[No_OF_Sentences][QUEUE_SIZE];
extern queueStatus_t status_2D;
extern u8 CHECK,N,in_QP_2D,Size_2D,Enter1,Enter2;
void rx_func_2D(void)
{
	UART_2DCircular_inQueue();
	if(status_2D==QUEUE_EMPTY && UART_Queue2D[Enter1][Enter2]==0x0d)
	{
		N++;
		in_QP_2D=0;
		/*			Size_2D--;*/
		status_2D=QUEUE_DONE;
	}
	if(status_2D==QUEUE_FULL)
	{
		LCD_GoTo(1,0);
		LCD_WriteString("Queue Full!   ");
		CHECK=UART_ReceiveNoBlock();
		if(CHECK==0x0d)
		{
			N++;
			in_QP_2D=0;
/*			Size_2D--;*/
			status_2D=QUEUE_DONE;
			CHECK=0;
		}
	}
	else if(status_2D==QUEUE_EMPTY)
	{
		status_2D=QUEUE_DONE;
	}
	
}

/**********************************************************/
ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}