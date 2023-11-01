/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: SPI.c	        	 */
/*****************************************/

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI.h"
// 
// static void(*UART_RX_Fptr)(void)=NULLPTR;
// static void(*UART_TX_Fptr)(void)=NULLPTR;


void SPI_Init(void)
{
	//SLAVE OR MASTER
	#if SPI_MODE
	SET_BIT(SPCR,MSTR);
	//clock		2MHZ

	#else
	CLR_BIT(SPCR,MSTR);
	//enable
	#endif
	SET_BIT(SPCR,SPE);
}

u8 SPI_SendReceive(u8 data)
{
	//write puffer
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF));
	//return puffer
	return SPDR;
}

u8 SPI_ReceivePeriodic(u8* pdata)
{
		if(READ_BIT(SPSR,SPIF))
		{
			*pdata=SPDR;
			return 1;
		}
		return 0;
}

u8 SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}