/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.1                      */
/*     Description: SPI.h	        	 */
/*****************************************/

#ifndef SPI_H_
#define SPI_H_

#define MASTER 1
#define SLAVE 0


#define SPI_MODE	MASTER


void SPI_Init(void);

u8 SPI_SendReceive(u8 data);

u8 SPI_ReceivePeriodic(u8* pdata);

u8 SPI_SendNoBlock(u8 data);

#endif /* SPI_H_ */