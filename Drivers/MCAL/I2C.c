/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 3/11/2023                   */
/*     Version:	V.1                      */
/*     Description: I2C.c		         */
/*****************************************/


#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "I2C_Interface.h"


void TWI_Init(void)
{
	//set SCL to 400kHz
	TWSR = 0x00;
	
	TWBR = 1; //CPU clock 8Mhz
	
	SET_BIT(TWCR,TWEN);	//enable TWI
}

void TWIStart(void)	/* I2C start function */
{
    SET_BIT(TWCR,TWSTA);		//Start Condition 
    SET_BIT(TWCR,TWINT);		//Interrupt flag
   
    while ((TWCR & (1<<TWINT)) == 0);
}

void TWIStop(void)												
{
	SET_BIT(TWCR,TWSTO);		
	SET_BIT(TWCR,TWINT);		//Interrupt flag
	while(TWCR & (1<<TWINT));								
}

void TWIWrite(u8 data)
{					
	TWDR = data;	
	CLR_BIT(TWCR,TWSTA);		//Start condition cleared
	SET_BIT(TWCR,TWINT);		//Interrupt flag		
	while ((TWCR & (1<<TWINT)) == 0);							
}
u8 TWIRead_data(void)											
{
	SET_BIT(TWCR,TWEA);			//Sending Ack
	CLR_BIT(TWCR,TWSTA);		//Start condition cleared
	SET_BIT(TWCR,TWINT);		//Interrupt flag
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

u8 Read_status(void)
{
	u8 status;
	status= TWSR & 0xF8;
	return status;
}