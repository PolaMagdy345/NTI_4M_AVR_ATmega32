/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: UART_Interface.h   	 */
/*****************************************/


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_Init();

void UART_Send(u8 data);

u8 UART_Receive(void);

u8 UART_ReceivePeriodic(u8* Pdata);

void UART_SendString(u8* str);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_SendNoBlock(u8 data);
u8 UART_ReceiveNoBlock(void);


void rx_func_2D(void);
void rx_func(void);
#endif /* UART_INTERFACE_H_ */