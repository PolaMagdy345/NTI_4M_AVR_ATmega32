/********************************************************************************/
/*								Author: Paula Magdy								*/
/*								Date:	26/10/2023								*/
/*								Version:	V.1									*/
/*								Description: KeyPad_Cfg.h						*/
/********************************************************************************/

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_


#define ROWS 4		//OUTPUT
#define COLS 4		//INPUT

#define FIRST_OUTPUT	PINC2
#define FIRST_INPUT		PIND3
#define NO_KEY	'T'

#if KEYPAD_PRG

const u8 KeysArr[ROWS][COLS]={{'7','8','9','/'}
							 ,{'4','5','6','*'}
						     ,{'1','2','3','-'}
						     ,{'C','0','=','+'}};
						
#endif
#endif /* KEYPAD_CFG_H_ */