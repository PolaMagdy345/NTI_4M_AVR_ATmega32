/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: UART_Services.c      */
/*****************************************/

#include "StdTypes.h"
#include "UART_Interface.h"
#include "UART_Services.h"

#define EVEN   1
#define ODD    0
#define PARITY  EVEN

u8 UART_Data[30],ArrStack;
 
void UART_SendString(u8* str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}

void UART_ReceiveString(u8* str)
{
	u8 i=0;
	str[0]=UART_Receive();
	for(;str[i]!=0x0d && str[i]!=0x0a;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
	str[i+1]=0;
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));

}

u32 UART_ReceiveNumber(void)
{
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	u32 num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	return num;
}

void UART_SendNumber2(u32 num)
{
	u8*p=(u8*)(&num);
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);

}

u32 UART_ReceiveNumber2(void)
{
	u8*p;
	u32 num;
	p=&num;
	
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	
	return num;
}

u8 endian_check(void)
{
	u32 num=1;
	u8*p=&num;
	if(*p==1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

u32 endian_converter_u32(u32 num)			//our system is little endian and that mean we must use this function to send the large byte so that it
{											//will be sent to UART from little byte to large one which is the right number we need to send :)
	u32 num2;
	num2=num>>24|num<<24|((num>>8)&0x0000ff00)|((num<<8)&0x00ff0000);		//00 00 00 00 00 00 00 00 00
	return num2;
}

void UART_SendStringCheckSum(u8* str)
{
	u8 i,l;
	u16 sum=0;
	for(l=0;str[l];l++)
	{
		sum+=str[l];
	}
	UART_Send(l);
	for(i=0;str[i];i++) 
	{
		UART_Send(str[i]);
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
	
}

u8 UART_ReceiveStringCheckSum(u8* str)
{
	u8 i,b0,b1,l=UART_Receive();
	
	u16 sum_rec=0,sum_calc=0;
	for(i=0;i<l;i++)
	{
		str[i]=UART_Receive();
		sum_calc+=str[i];
	}
	b0=UART_Receive();
	b1=UART_Receive();
	sum_rec=b0|b1<<8;
	if(sum_rec==sum_calc)
	{
		return 1;
	}
	else
	return 0;
}

u16 UART_Frame(u8 data)			//suppose data 00001001
{
	u16 frame=0x0400;		//0000 0010 0000 0000
	u8 ones=0;
	u8 parity;
	frame|=data<<1;			//00010010
	while(data)
	{
		ones+=data&1;
		data>>=1;
	}
	if(PARITY==EVEN)
	{
		if(ones%2==0)
		{
			parity=0;
		}
		else
		{
			parity=1;
		}
	}
	else
	{
		if(ones%2==0)
		{
			parity=1;
		}
		else
		{
			parity=0;
		}
	}
	frame=frame|(PARITY<<9);		//1000010010
	
	return frame;
}

void UART_SendFrame(u16 frame)
{
	for(u8 i=0;i<11;i++)
	{
		
	}
}
static void tx_func(void);
static u8*Str_TX;
void UART_SendStringAsync(u8*str)
{
	UART_Send(str[0]);
	Str_TX=str;
	UART_TX_InterruptEnable();
	UART_TX_SetCallBack(tx_func);
}

static void tx_func(void)
{
	static u8 i=1;
	if(Str_TX[i]!=0)
	{
		UART_SendNoBlock(Str_TX[i]);
		i++;
	}
	else
	{
		i=1;
	}
}

static u8 in_QP,De_QP;
u8 UART_Queue[QUEUE_SIZE];
static u8 In_Flag;
queueStatus_t status;

queueStatus_t UART_Circular_inQueue(void)		//UART_inQueue (Receive NoBlock Data)
{
	if((in_QP>=De_QP && In_Flag==0) || (in_QP<De_QP && In_Flag==1))
	{
		UART_Queue[in_QP]=UART_ReceiveNoBlock();
		in_QP++;
		status=QUEUE_DONE;
	}
	else if(in_QP==De_QP && In_Flag==1)
	{
		status=QUEUE_FULL;
	}
	if(in_QP==QUEUE_SIZE)
	{
		In_Flag=1;
		in_QP=0;
	}
	return status;
}

queueStatus_t UART_Circular_deQueue(void)				//UART_deQueue (Send NoBlock Data)
{

	if((De_QP<in_QP && In_Flag==0)|| (De_QP>=in_QP && In_Flag==1))
	{                                                           //||(De_QP<QUEUE_SIZE && In_Flag==1)
		De_QP++;
		//printf("De_QP: %d\n",De_QP);
		status=QUEUE_DONE;
	}
	else if(De_QP==in_QP && In_Flag==0)
	{
		status=QUEUE_EMPTY;
	}
	else
	status=QUEUE_EMPTY;
	if(De_QP==QUEUE_SIZE)
	{
		In_Flag=0;
		De_QP=0;
	}

	return status;
}
/************************2D Sentences Queue******************************/


u8  in_QP_2D,De_QP_2D,Size_2D,De_QTotal,CHECK;
u8 UART_Queue2D[No_OF_Sentences][QUEUE_SIZE];
u8 In_Flag_2D,N,Enter1,Enter2;
queueStatus_t status_2D;

queueStatus_t UART_2DCircular_inQueue(void)		//UART_inQueue (Receive NoBlock Data)
{
	if((Size_2D>=De_QTotal && In_Flag_2D==0 && in_QP_2D<QUEUE_SIZE) || (Size_2D<De_QTotal && In_Flag_2D==1))
	{
		if(UART_Queue2D[N][in_QP_2D-1]==0x0d /*|| UART_Queue2D[N][in_QP_2D-1]==0x0a*/)
		{
			Enter1=N;
			Enter2=in_QP_2D-1;
			N++;
			in_QP_2D=0;
			Size_2D--;
		}
		UART_Queue2D[N][in_QP_2D]=UART_ReceiveNoBlock();
		in_QP_2D++;
		status_2D=QUEUE_DONE;
		Size_2D++;
	}
	else if(in_QP_2D==QUEUE_SIZE || in_QP_2D==De_QP_2D)
	{
		UART_Queue2D[N][in_QP_2D]=UART_ReceiveNoBlock();
		if(UART_Queue2D[N][in_QP_2D]==0X0d)
		{
			in_QP_2D=0;
			N++;
			status_2D=QUEUE_DONE;
		}
		status_2D=QUEUE_FULL;
	}
	if(in_QP_2D==QUEUE_SIZE && Size_2D==(No_OF_Sentences*QUEUE_SIZE))
	{
		In_Flag_2D=1;
		in_QP_2D=0;
	}
	return status_2D;
}

queueStatus_t UART_2DCircular_deQueue(void)				//UART_deQueue (Send NoBlock Data)
{
	if(UART_Queue2D[N][De_QP_2D]==0x0d)
	{
		De_QP_2D=0;
	}
	if((De_QTotal<Size_2D && In_Flag_2D==0) || (De_QTotal>=Size_2D && In_Flag_2D==1 ))
	{                                                           //||(De_QP<QUEUE_SIZE && In_Flag==1)
		De_QP_2D++;
		De_QTotal++;
		//printf("De_QP: %d\n",De_QP);
		status_2D=QUEUE_DONE;
	}
	else if(De_QTotal==Size_2D && In_Flag_2D==0)
	{
		status_2D=QUEUE_EMPTY;
	}
	else
	status_2D=QUEUE_EMPTY;
	if(De_QP_2D==QUEUE_SIZE)
	{
		In_Flag_2D=0;
		De_QP_2D=0;
	}

	return status_2D;
}


/**********************************************************************/

/*
u8 i=0;
void UART_Queue_Runnable(void)
{
	if(!DIO_ReadPin(PINC4))
	{
		if(UART_Circular_deQueue()==QUEUE_DONE)
		{
			LCD_GoTo(0,0);
			LCD_WriteString("DeQueue Done!");
			LCD_GoTo(1,i);
			LCD_WriteChar(UART_Queue[i]);
			i++;
		}
		else if(UART_Circular_deQueue()==QUEUE_EMPTY)
		{
			LCD_GoTo(0,0);
			LCD_WriteString("Queue Empty!");
			LCD_GoTo(1,0);
			LCD_WriteString("             ");
			i=0;
		}
	}
}*/