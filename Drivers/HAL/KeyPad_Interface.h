/*****************************************/
/*     Author: Paula Magdy               */
/*     Date: 1/11/2023                   */
/*     Version:	V.2                      */
/*     Description: KeyPad_Interface.h   */
/*****************************************/


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
#include "KeyPad_Cfg.h"
void KEYPAD_Init(void);

u8 KEYPAD_Getkey(void);


u8 KEYPAD_Binary(void);



#endif /* KEYPAD_INTERFACE_H_ */