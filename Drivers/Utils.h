/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 26/10/2023                  */
/*     Version:	V.1                      */
/*     Description: Utils.h              */
/*****************************************/

#ifndef UTILS_H_
#define UTILS_H_


#define READ_BIT(reg,bit)    ((reg>>bit)&1)
#define SET_BIT(reg,bit)    (reg=reg|(1<<bit))
#define CLR_BIT(reg,bit)    (reg=reg&(~(1<<bit)))
#define TGL_BIT(reg,bit)    (reg=reg^(1<<bit))

#define SET_BYTE(byte,value)	(byte=value)

#define F_CPU 8000000
#include <util/delay.h>



#endif 
