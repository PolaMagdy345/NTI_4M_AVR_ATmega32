/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 3/11/2023                   */
/*     Version:	V.1                      */
/*     Description: I2C_Interface.h      */
/*****************************************/

#ifndef I2C_INTEFACE_H_
#define I2C_INTEFACE_H_

void TWI_Init(void);
void TWIStart(void);
void TWIStop(void);
void TWIWrite(u8 data);
u8 TWIRead_data(void);
u8 Read_status(void);

	



#endif /* I2C_INTEFACE_H_ */