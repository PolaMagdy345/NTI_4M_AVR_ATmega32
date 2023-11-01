/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: UART_Services.h      */
/*****************************************/


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

/*
*		synch function
*		blocking
*/
#define QUEUE_SIZE 15
#define No_OF_Sentences		10
typedef enum
{
	QUEUE_DONE,
	QUEUE_FULL,
	QUEUE_EMPTY
}queueStatus_t;


void UART_SendString(u8* str);

void UART_ReceiveString(u8* str);

void UART_SendNumber(u32 num);
u32 UART_ReceiveNumber(void);

void UART_SendNumber2(u32 num);
u32 UART_ReceiveNumber2(void);

u8 endian_check(void);

u32 endian_converter_u32(u32 num);		//our system is little endian and that mean we must use this function to send the large byte so that it
										//will be sent to UART from little byte to large one which is the right number we need to send :)


void UART_SendStringCheckSum(u8* str);

u8 UART_ReceiveStringCheckSum(u8* str);

u16 UART_Frame(u8 data);			//suppose data 00001001

void UART_SendFrame(u16 frame);

void UART_SendStringAsync(u8*str);

queueStatus_t UART_Circular_inQueue(void);
queueStatus_t UART_Circular_deQueue(/*u8* data*/void);
queueStatus_t UART_2DCircular_inQueue(void);		//UART_inQueue (Receive NoBlock Data)
queueStatus_t UART_2DCircular_deQueue(void)	;			//UART_deQueue (Send NoBlock Data)

#endif /* UART_SERVICES_H_ */